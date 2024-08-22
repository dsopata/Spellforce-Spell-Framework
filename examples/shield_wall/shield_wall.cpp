#include "../../api/sfsf.h"
#include <windows.h>
#include <stdio.h>


// We declare macros for Spell Type and Spell Job of both spells
// it is very unhandy to keep them in mind, so we just declare them here
// we use a new set of numbers to avoid interfering with previous examples
// 0xf3 = 243, 0xaa = 170, 0xf4 = 244, 0xab = 171

// The custom Spell Types (243 and 244) also must be defined within GameData.cff
// and provided with at least one spell corresponding each Spell Type

#define SHIELD_WALL_LINE 0xf3
#define SHIELD_WALL_JOB 0xaa
#define PARRY_LINE 0xf4
#define PARRY_JOB 0xab


SpellforceSpellFramework *sfsf;
SpellFunctions *spellAPI;
ToolboxFunctions *toolboxAPI;
FigureFunctions *figureAPI;
IteratorFunctions *iteratorAPI;
RegistrationFunctions *registrationAPI;
//SFLog *logger

/* debug output example
Let it be here
char aliveInfo[256];
sprintf(aliveInfo, "Flags list: Target %hd \n", target_index);
logger->logInfo(aliveInfo);
*/

// we declare spell type handler for PARRY
// PARRY is a second component of an AoE spell
// it implements an armor buff for a single target
// it is triggered individually for each target when the AoE spell affects them
void __thiscall parry_type_handler(SF_CGdSpell *_this, uint16_t spell_index)
{
    // we associate spell type with a spell job
    _this->active_spell_list[spell_index].spell_job = PARRY_JOB;
    // we initialize values for a spell, SPELL_TICK_COUNT_AUX is familiar from previous example, it controls amount of spell ticks passed for this specific spell
    // ticks stand for multiple times when the same spell affects the target
    // however, this spell will use only two ticks at all
    // 0 for beginning to apply buff
    // 1 for ending to remove effect
    spellAPI->setXData(_this, spell_index, SPELL_TICK_COUNT_AUX, 0);

    // SPELL_STAT_MUL_MODIFIER will store a percentage by which the target's armor was increased
    // the percentage will be individual for every figure depending on its previous armor rating
    spellAPI->setXData(_this, spell_index, SPELL_STAT_MUL_MODIFIER, 0);
}

// we declare spell end handler for PARRY
// this handler would work in case a spell wasn't finished correctly
void __thiscall parry_end_handler(SF_CGdSpell *_this, uint16_t spell_index)
{
    SF_GdSpell *spell = &_this->active_spell_list[spell_index];
    uint16_t target_index = spell->target.entity_index;
    spellAPI->removeDLLNode(_this, spell_index); // we remove spell from the list of active spells over the target
    spellAPI->setEffectDone(_this, spell_index, 0); // we end a spell

    // we pull the percentage by which the target's armor rating was increased
    uint16_t recalc_value = spellAPI->getXData(_this, spell_index, SPELL_STAT_MUL_MODIFIER);
    // we remove the bonus to target's armor rating by adding negative amount of this value
    figureAPI->addBonusMultToStatistic(_this->SF_CGdFigure, ARMOR, target_index, -recalc_value);

    // here you might see the legacy of attempt to implement flat bonus to armor
    // it's not functional because armor.bonus_val can be overwritten by worn armor whenever you reequip it
    //_this->SF_CGdFigure->figures[target_index].armor.bonus_val += -recalc_value;
}


//we declare effect handler which implements game logic for parry effect
void __thiscall parry_effect_handler(SF_CGdSpell *_this, uint16_t spell_index)
{
    SF_GdSpell *spell = &_this->active_spell_list[spell_index];

    //the PARRY spell is directly applied to a figure
    //we get the target index of affected figure
    //however, it's worth of mentioning, that the source_index would return the index of a figure which casted SHIELDWALL (initial component implementing AoE logic of the spell) in case we want to do something with a caster

    uint16_t target_index = spell->target.entity_index;

    // we get the current tick of the spell, should be 0 at the beginning, and 1 in the end
    uint32_t current_tick = spellAPI->getXData(_this, spell_index, SPELL_TICK_COUNT_AUX);
    // we increase amount of ticks passed by 1
    spellAPI->addToXData(_this, spell_index, SPELL_TICK_COUNT_AUX, 1);

    //we declare a structure for spell to store spell parameters which we will load from GameData.cff
    SF_CGdResourceSpell spell_data;
    spellAPI->getResourceSpellData(_this->SF_CGdResource, &spell_data, spell->spell_id);

    //we load interval specified in milliseconds between the beginning and the ending ticks from GameData.cff
    uint16_t ticks_interval = spell_data.params[1];



    if (current_tick == 0)
    // this is the first tick
    // we're going to add buff to a target and then make the spell to wait for specified amount of time
    {

        // the default armor rating is defined by base armor rating and bonus armor rating
        // worn armor actually changes bonus armor rating, so to make spell work properly we have to sum both values
        uint16_t figure_ac = _this->SF_CGdFigure->figures[target_index].armor.base_val + _this->SF_CGdFigure->figures[target_index].armor.bonus_val;

        // we're going to work with percentile values, so it's better to temporarily record them to float variable
        double recalc_temp = spell_data.params[0] - figure_ac;
        recalc_temp = recalc_temp / figure_ac * 100;

        // however, game engine uses percentiles in their natural expression, e.g. 80 instead of 0.8
        // that's why we multiply them by 100 above and transform into integer thereafter
        uint16_t recalc_value = uint16_t (recalc_temp);

        // due to engine limitations, maximum bonus multiplier is limited by uint8_t range, hence by {-127%, 128%}
        // to prevent our argument going overflow, let's nudge it to something smaller
        if (recalc_value > 100)
            recalc_value = 100;
        else
            if (recalc_value < - 100)
        recalc_value = -100;


        // we're adding the bonus to figure statistic
        // game automatically calculates multiplied armor rating value in the next game tick (not to be confused with spell tick)
        figureAPI->addBonusMultToStatistic(_this->SF_CGdFigure, ARMOR, target_index, recalc_value);

        // _this->SF_CGdFigure->figures[target_index].armor.bonus_val += recalc_value;
        // alternatively it could be possible to add value as flat bonus with bonus_val
        // but won't work properly, because this key directly overwritten by worn armor


        // we record multiplier directly within the spell, to remove the same percentage when the spell ends
        spellAPI->setXData(_this, spell_index, SPELL_STAT_MUL_MODIFIER, recalc_value);

        // we disable the spell from being triggered for a specified number of internal game ticks, and after a specified in ticks_interval amount of time has passed, we may remove the spell
        _this->active_spell_list[spell_index].to_do_count = (uint16_t)((ticks_interval * 10) / 1000);
        return;
    }
    else
    // current tick is 1, it means the spell has ended and we have to remove the bonus provided by it
    {
        // we retrieve the armor multiplier directly from the spell instance
        uint16_t recalc_value = spellAPI->getXData(_this, spell_index, SPELL_STAT_MUL_MODIFIER);
        // we add negative value of this multiplier to figure's statistic
        figureAPI->addBonusMultToStatistic(_this->SF_CGdFigure, ARMOR, target_index, -recalc_value);


        // keeping it to show how it could be possibly done in flat way
        // but it can't be actually used due to interference with other instances using bonus_val as well
        //_this->SF_CGdFigure->figures[target_index].armor.bonus_val += -recalc_value;

        // we end the spell
        spellAPI->setEffectDone(_this, spell_index, 0);
        return;
    }
}


//we declare spell type handler for AoE spell
//the SHIELDWALL is supposed to be triggered first, it initializes spell AoE logic
void __thiscall shield_wall_type_handler(SF_CGdSpell *_this, uint16_t spell_index)
{
    // we link the specific spell type with its own spell job
    _this->active_spell_list[spell_index].spell_job = SHIELD_WALL_JOB;
}

// we declare spell effect handler which implements game logic of the AoE spell
// the AoE checks for a specified amount of targets in a certain radius around the spellcaster
// if the spell happens to affect again before the previous instance expired, it resets its duration
// spell effect is simulated by individual instances of PARRY spell applied to every target affected

void __thiscall shield_wall_effect_handler(SF_CGdSpell *_this, uint16_t spell_index)
{
    // we pull the pointer for this instance of spell
    SF_GdSpell *spell = &_this->active_spell_list[spell_index];

    // we store index of the spellcaster
    uint16_t source_index = _this->active_spell_list[spell_index].source.entity_index;

    // we load the spell parameters from GameData.cff
    // we'll use them later
    SF_CGdResourceSpell spell_data;
    spellAPI->getResourceSpellData(_this->SF_CGdResource, &spell_data, spell->spell_id);


    // we declare structure to specify the area affected by the AoE effect
    SF_Rectangle hit_area;

    // we declare structure to store the center of the spell
    SF_Coord cast_center;
    // we get XY coordinates of the spell center with API function
    // basically, we just center the spell around its spellcaster (source)
    figureAPI->getPosition(_this->SF_CGdFigure, &cast_center, source_index);

    // we declare structure for relative position of visual effect
    SF_CGdTargetData relative_data;
    relative_data.position = {_this->active_spell_list[spell_index].source.position.X, _this->active_spell_list[spell_index].source.position.Y};
    relative_data.entity_type = 4;
    relative_data.entity_index = 0;
    uint32_t unused;

    // we get coordinates of area affected and record them as a squared circle
    // spell_data.params[0] stands for a spell radius
    // the radius is measured in game units, 10-15 is enough for quite big spell area
    spellAPI->getTargetsRectangle(_this, &hit_area, spell_index, spell_data.params[0], &cast_center);

    // we apply the visual effect filling the area which we specified above
    spellAPI->addVisualEffect(_this, spell_index, kGdEffectSpellHitWorld, &unused, &relative_data, _this->OpaqueClass->current_step, 0x19, &hit_area);


    // we declare an iterator
    // iterator is a class which searches for targets (figures) in certain area
    // iterators are opaque from the user perspective.
    // just give enough memory and don't bother what's inside
    CGdFigureIterator figure_iterator;
    iteratorAPI->setupFigureIterator(&figure_iterator, _this);
    // we set iterator area as a circle of specific radius (defined in spell data) with the spellcaster being at its center
    iteratorAPI->iteratorSetArea(&figure_iterator, &cast_center, spell_data.params[0]);

    // let's make spellcaster our first target and give them spell effect for free
    // we could initiate the search for the first target with iterator API function
    // target_index = iteratorAPI->getNextFigure(&figure_iterator);
    // but getNextFigure not always gives the source as first result, so let's add some safeguard here

    uint16_t target_index = source_index;

    // the spell can affect only certain amount of figures
    // we load this amount from spell parameters in GameData.cff
    uint16_t figure_count = spell_data.params[1];

    //we promised to give spellcaster effect for free, let's increase the amount of affected figures by 1
    figure_count++;

    while (target_index != 0 && figure_count != 0)
    // we apply the spell as long as there are viable targets around and as long as we didn't exceed figures limit
    {
        // we apply the spell only to living figures belonging to our own faction, as long as those figures are targetable
        // notice that we affect those flags directly via respective structures rather than with API functions as in previous example
        // both options are allowable
        if (((int16_t)(_this->SF_CGdFigure->figures[target_index].owner) == (int16_t)(_this->SF_CGdFigure->figures[source_index].owner)) &&
            (((uint8_t)(_this->SF_CGdFigure->figures[target_index].flags) & 0xa) == 0) &&
            (toolboxAPI->isTargetable(_this->SF_CGdFigureToolBox, target_index)))
        {
            // we also can't apply the spell to target if the target is already affected with another instance of the spell
            // checkCanApply triggers the refresh handler for a spell specified via its spell_index (SHIELDWALL in this case)
            // if checkCanApply returns false, it means the PARRY already affects the target
            spell->target.entity_index = target_index;
            // checkCanApply addresses the same spell which we're currently working with (SHIELDWALL)
            // however, we have to know the index of the target which the iterator returned for us
            // because we can't pass target index directly, we change target index within the spell itself
                if (spellAPI->checkCanApply(_this, spell_index))
                {
                    // checkCanApply returned 1 here, so we add the spell to a long validated target
                    // to do this, we declare structures for source and target to trigger another component (wrapped as its own spell) within the AoE spell
                    SF_CGdTargetData source = {spell->source.entity_type, source_index, {0, 0}};
                    SF_CGdTargetData target = {spell->source.entity_type, target_index, {0, 0}};
                    // we apply PARRY spell to a single specific target (the spellcaster)
                    // we have equated a source and a target in this case
                    // spell_data.params[3] stands for PARRY spell data id which we're going to apply to the target
                    // _this->OpaqueClass->current_step stands for the spell starting tick (meaning game ticks, not spell tick)
                    // it's unknown what's the last parameter is standing for
                    spellAPI->addSpell(_this, spell_data.params[3], _this->OpaqueClass->current_step, &source, &target, 0);

                    // we spent one usage of the spell, hence we decrease the possible limit by one
                    // but if we applied the spell to a spellcaster, let's give it for free
                    figure_count--;
                }
        }
        // we search for the next target with iterator API function
        target_index = iteratorAPI->getNextFigure(&figure_iterator);
    }
    // all figures in radius were checked or all usages of spell was spent, we finish the SHIELDWALL spell
    spellAPI->setEffectDone(_this, spell_index, 0);

    // we release the memory which we allocated for iterator
    iteratorAPI->disposeFigureIterator(figure_iterator);
}


// we declare refresh handler for AoE spell
// this handler will be called whenever we're casting shieldwall, and will remove previously casted shieldwall if there is any
int __thiscall shield_wall_refresh_handler(SF_CGdSpell *_this, uint16_t spell_index) //we casted shieldwall again before the previous expired
{
    SF_GdSpell *spell = &_this->active_spell_list[spell_index];
    // we declare target index with value which we stored into SHIELDWALL spell above
    uint16_t target_index = spell->target.entity_index;

    // we declare spell_data for SHIELDWALL spell, because we need to pull the spell id of PARRY spell linked with SHIELDWALL spell
    SF_CGdResourceSpell spell_data;
    spellAPI->getResourceSpellData(_this->SF_CGdResource, &spell_data, spell->spell_id);

    // we declare own spell_data for PARRY spell
    SF_CGdResourceSpell spell_data_2;
    spellAPI->getResourceSpellData(_this->SF_CGdResource, &spell_data_2, spell_data.params[3]);

    // we check whether the figure has the PARRY spell applied to it already
    // method hasSpellOnIt accepts spell_line_id property of spell data as argument in order to idenfity the spell
    if (toolboxAPI->hasSpellOnIt(_this->SF_CGdFigureToolBox, target_index, spell_data_2.spell_line_id))
       // the PARRY spell already exists on the target
        {

            /***
            * This is outdated implementation of refresh_handler
            * it could be used to automatically remove a previous instance of PARRY spell
            * so the spell will effectively reset its duration on a recast
            ***/
            /*
            // here comes the magic
            // we can get the spell index from the list of active spells affecting the target by knowing this spell's spell job id
            // we pass SHIELDWALL spell_index as the last known spell index for this figure, but this value is insignificant (used for optimizing search purposes?)
            uint16_t parry_spell_index = toolboxAPI->getSpellIndexOfType(_this->SF_CGdFigureToolBox, target_index, PARRY_LINE, spell_index);

            // we should remove the bonus provided with the instance of the spell we're going to remove
            // knowing spell index, we can get the bonus multiplier to the armor rating
            uint16_t recalc_value = spellAPI->getXData(_this, parry_spell_index, SPELL_STAT_MUL_MODIFIER);
            // we remove it in the usual way, by adding its negative value to figure's statistic
            figureAPI->addBonusMultToStatistic(_this->SF_CGdFigure, ARMOR, target_index, -recalc_value);
            // we finish the PARRY spell using its spell index
            spellAPI->setEffectDone(_this, parry_spell_index, 0);
            */
            return 0;
        }
    else
        // the target isn't affected by the PARRY spell
        {
            // we return true for checkCanApply()
            // we leave this block empty, because we actually had to check for another spell within the initial one (the one which triggered the refresh handler)
            // however, in case we had to check only for the one spell, we could use checkCanApply() function as a real condition check
            // or we could forbid the SHIELDWALL from being reset
            // and make it to be allowed to cast on target, only in case checkCanApply() returned 1
            return 1;
        }
}



/***
 * This function MUST be present in your code with the exact declaration
 * otherwise framework won't load your plugin
 ***/
extern "C" __declspec(dllexport) void InitModule(SpellforceSpellFramework *framework)
{
    // we pull pointers to framework methods and structures
    sfsf = framework;
    spellAPI = sfsf->spellAPI;
    toolboxAPI = sfsf->toolboxAPI;
    figureAPI = sfsf->figureAPI;
    iteratorAPI = sfsf->iteratorAPI;
    registrationAPI = sfsf->registrationAPI;


    // we register handlers for AoE component of the spell
    // in this example we introduce new handler - spell refresh handler
    // this handler will be called to implement game logic for situations when we cast spell on a unit which is already affected by this spell
    SFSpell *shield_wall_spell = registrationAPI->registerSpell(SHIELD_WALL_LINE);
    registrationAPI->linkTypeHandler(shield_wall_spell, &shield_wall_type_handler);
    registrationAPI->linkEffectHandler(shield_wall_spell, SHIELD_WALL_JOB, &shield_wall_effect_handler);
    registrationAPI->linkRefreshHandler(shield_wall_spell, &shield_wall_refresh_handler);

    // we register handlers for target component of the spell
    // notice, that in Ignite example we defined Spell Type (PARRY_LINE) and Spell Job (PARRY_JOB) with real numbers
    // here we just use macros to automatize the assignation
    SFSpell *parry_spell = registrationAPI->registerSpell(PARRY_LINE);
    registrationAPI->linkTypeHandler(parry_spell, &parry_type_handler);
    registrationAPI->linkEffectHandler(parry_spell, PARRY_JOB, &parry_effect_handler);
    registrationAPI->linkEndHandler(parry_spell, &parry_end_handler);
}

/***
 * This function MUST be present in your code with the exact declaration
 * otherwise the framework is unable to describe your mod in logs and mod info menu (menu not yet implemented)
 ***/
extern "C" __declspec(dllexport) SFMod *RegisterMod(SpellforceSpellFramework *framework)
{
    return framework->createModInfo("Shield wall Mod", "1.0.0", "UnSchtalch, Teekius", "A mod designed to demonstrate spell providing temporary AoE buff to player-controlled units.");
}

// Required to be present by, not required for any functionality
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        /* Code path executed when DLL is loaded into a process's address space. */
        break;

    case DLL_THREAD_ATTACH:
        /* Code path executed when a new thread is created within the process. */
        break;

    case DLL_THREAD_DETACH:
        /* Code path executed when a thread within the process has exited *cleanly*. */
        break;

    case DLL_PROCESS_DETACH:
        /* Code path executed when DLL is unloaded from a process's address space. */
        break;
    }

    return TRUE;
}
