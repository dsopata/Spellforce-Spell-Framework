#include "sf_onhit_hook.h"
#include "../sf_wrappers.h"
#include "../sf_hooks.h"
#include "../sf_modloader.h"
#include "../../registry/sf_onhit_registry.h"
#include "../../registry/sf_mod_registry.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <utility>

typedef uint16_t(__thiscall *get_reduced_damage_ptr)(void *AutoClass34, uint16_t source_index, uint16_t target_index, uint16_t unkn);
typedef uint16_t(__thiscall *get_hit_chance_ptr)(void *AutoClass34, uint16_t source_index, uint16_t target_index);

typedef void(__thiscall *FUN_006c3a60_ptr)(void *AutoClass30, uint16_t source_index, uint16_t target_index, uint8_t unkn, uint32_t unkn2);

get_reduced_damage_ptr g_get_reduced_damage;
get_hit_chance_ptr g_get_hit_chance;
FUN_006c3a60_ptr g_FUN_006c3a60;
void initialize_onhit_data_hooks()
{
    g_get_reduced_damage = (get_reduced_damage_ptr)(ASI::AddrOf(0x3177d0));
    g_get_hit_chance = (get_hit_chance_ptr)(ASI::AddrOf(0x317860));
    g_FUN_006c3a60 = (FUN_006c3a60_ptr)(ASI::AddrOf(0x2c3a60));
}

void __thiscall getTargetData(AutoClass24 *_this, SF_CGdTargetData *target)
{
    target->entity_type = _this->target.entity_type;
    target->entity_index = _this->target.entity_index;
    target->position = _this->target.position;
}

uint32_t getDistange(SF_Coord *pointA, SF_Coord *pointB)
{

    uint32_t delta;
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t uVar4;

    delta = (uint32_t)(uint16_t)pointA->X - (uint32_t)(uint16_t)pointB->X;
    uVar2 = (int)delta >> 0x1f;
    uVar2 = (delta ^ uVar2) - uVar2;
    uVar4 = uVar2 & 0xffff;
    delta = (uint32_t)(uint16_t)pointA->Y - (uint32_t)(uint16_t)pointB->Y;
    uVar3 = (int)delta >> 0x1f;
    uVar3 = (delta ^ uVar3) - uVar3;
    uVar1 = uVar3 & 0xffff;
    delta = uVar1;
    if ((uint16_t)uVar2 < (uint16_t)uVar3)
    {
        delta = uVar4;
        uVar4 = uVar1;
    }
    return ((delta * 0xd) >> 5) + uVar4;
}

bool isJobDoNothing(uint16_t job_id)
{
    if ((job_id == kGdJobGroupNothing) || (job_id == kGdJobWarriorNothing) ||
        (job_id == kGdJobCheckBattleSleep) || (job_id == kGdJobPetIdle))
    {
        return 1;
    }
    return 0;
}

bool __thiscall isFigureJobSpell(SF_CGdFigureJobs *_this, uint16_t figure_id)
{
    uint16_t job_id = figureAPI.getJob(_this->CGdFigure, figure_id);
    if ((job_id == kGdJobCast) || (job_id == kGdJobPreCast) || (job_id == kGdJobCastResolve) || (job_id == kGdJobCastPreResolve))
    {
        return 1;
    }
    if (job_id == kGdJobWalkToTarget)
    {
        SF_SGtFigureAction action;
        figureAPI.getTargetAction(_this->CGdFigure, &action, figure_id);
        if ((action.type != 0) && (action.type < 10000))
        {
            return 1;
        }
    }
    return 0;
}

bool __thiscall canJobBeInterrupted(FigureJobs job_id)

{
    if ((((job_id != kGdJobCastPreResolve) && (job_id != kGdJobCastResolve)) &&
         (job_id != kGdJobHitTargetRange2)) &&
        (((job_id != kGdJobEnterBuilding && (job_id != kGdJobExitBuilding)) &&
          ((job_id != kGdJobMeleeAbility && (job_id != kGdJobStartWorkAtBuilding))))))
    {
        return 1;
    }
    return 0;
}

uint16_t __thiscall getAttackInterruptionChance(SF_CGdFigure *_this, uint16_t source_index, uint16_t target_index)
{
    uint8_t source_level = _this->figures[source_index].level;
    uint8_t target_level = _this->figures[target_index].level;
    if (target_level < source_level)
    {
        uint16_t precalc_chance = (source_level - target_level) * 5 + 0xf;
        if (precalc_chance > 100)
        {
            return 100;
        }
        return precalc_chance;
    }
    if (target_level == source_level)
    {
        return 0xf;
    }
    if (0xf < ((target_level - source_level) * 2))
    {
        return 0;
    }
    return (target_index - source_index) * -2 + 0xf;
}

uint16_t __thiscall handle_riposte_set(SF_CGdFigureJobs *_this, uint16_t source_index, uint16_t target_index, uint16_t weapon_damage)
{
    bool apply_set = false;
    if (_this->CGdFigure->figures[target_index].set_type == 0x03)
    {
        uint16_t counter = spellAPI.getRandom(_this->OpaqueClass, 100);
        apply_set = (counter < 0x0b);
    }
    if (apply_set)
    {
        uint16_t damage = g_get_reduced_damage(_this->AutoClass34, source_index, source_index, weapon_damage);
        toolboxAPI.dealDamage(_this->CGdFigureToolBox, source_index, source_index, damage, 0, 0, 0);
        return 0;
    }
    return weapon_damage;
}

uint16_t __thiscall handle_berserk_set(SF_CGdFigureJobs *_this, uint16_t source_index, uint16_t target_index, uint16_t weapon_damage)
{
    bool apply_set = false;
    if (_this->CGdFigure->figures[source_index].set_type == 0x04)
    {
        uint16_t counter = spellAPI.getRandom(_this->OpaqueClass, 100);
        apply_set = (counter < 0x0b);
    }
    // 7FFF is one-shot magic number
    if ((apply_set) && (weapon_damage != 0x7FFF))
    {
        uint16_t damage = weapon_damage * 3;
        return damage;
    }
    return weapon_damage;
}

uint16_t __thiscall handle_trueshot_set(SF_CGdFigureJobs *_this, uint16_t source_index, uint16_t target_index, uint16_t weapon_damage)
{
    bool apply_set = false;
    if (_this->CGdFigure->figures[source_index].set_type == 0x05)
    {
        uint16_t counter = spellAPI.getRandom(_this->OpaqueClass, 100);
        apply_set = (counter < 0x0b);
    }
    // 7FFF is one-shot magic number
    if ((apply_set) && (weapon_damage != 0x7FFF))
    {
        uint16_t damage = weapon_damage * 4;
        return damage;
    }
    return weapon_damage;
}

void __thiscall sf_onhit_hook(SF_CGdFigureJobs *_this, uint16_t source_index, uint32_t param_2, uint8_t param_3)
{
    log_info("Called Into On Hit");
    if ((_this->CGdFigure->figures[source_index].owner == -1) || (_this->CGdFigure->figures[source_index].flags & 10))
    {
        return;
    }

    SF_CGdFigureWeaponStats weapon_stats;
    SF_CGdTargetData target;
    SF_SGtFigureAction action;
    figureAPI.getWeaponStats(_this->CGdFigure, &weapon_stats, source_index);
    uint16_t weapon_damage = spellAPI.getRandom(_this->OpaqueClass, weapon_stats.max_dmg - weapon_stats.min_rng);
    weapon_damage += weapon_stats.min_dmg;
    getTargetData(&_this->CGdFigure->figures[source_index].ac_1, &target);
    figureAPI.getTargetAction(_this->CGdFigure, &action, source_index);

    if (target.entity_type == 1)
    {
        // donnoe wtf is it, looks like shooting?
        if (action.type == 0x2712)
        {
            uint16_t maxY = (_this->CGdFigure->figures[source_index].position.Y <= _this->CGdFigure->figures[target.entity_index].position.Y)
                                ? (_this->CGdFigure->figures[target.entity_index].position.Y)
                                : (_this->CGdFigure->figures[source_index].position.Y);

            uint16_t maxX = (_this->CGdFigure->figures[source_index].position.X <= _this->CGdFigure->figures[target.entity_index].position.X)
                                ? (_this->CGdFigure->figures[target.entity_index].position.X)
                                : (_this->CGdFigure->figures[source_index].position.X);

            uint16_t minY = (_this->CGdFigure->figures[source_index].position.Y > _this->CGdFigure->figures[target.entity_index].position.Y)
                                ? (_this->CGdFigure->figures[target.entity_index].position.Y)
                                : (_this->CGdFigure->figures[source_index].position.Y);

            uint16_t minX = (_this->CGdFigure->figures[source_index].position.X > _this->CGdFigure->figures[target.entity_index].position.X)
                                ? (_this->CGdFigure->figures[target.entity_index].position.X)
                                : (_this->CGdFigure->figures[source_index].position.X);
            SF_Coord p1;
            SF_Coord p2;
            SF_Rectangle vector;
            p1.X = maxX;
            if (minX < maxX)
            {
                p1.X = minX;
            }
            p1.Y = maxY;
            if (minY < maxY)
            {
                p1.Y = minY;
            }

            p2.X = maxX;
            if (maxX <= minX)
            {
                p2.X = minX;
            }
            p2.Y = maxY;
            if (maxY <= minY)
            {
                p2.Y = minY;
            }
            vector.partA = p1.Y << 0x10 | p1.X;
            vector.partB = p2.Y << 0x10 | p2.X;

            uint32_t distance = getDistange(&_this->CGdFigure->figures[source_index].position, &_this->CGdFigure->figures[target.entity_index].position);
            distance = ((distance & 0xffff) * 0x578) / 3000;
            SF_CGdTargetData source = {1, source_index, {0, 0}};
            uint16_t effect_id = effectAPI.addEffect(_this->CGdEffect, kGdEffectProjectile, &source, &target,
                                                     _this->OpaqueClass->current_step, ((distance != 0) ? distance : 1), &vector);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_ENTITY_TYPE, 1);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_ENTITY_TYPE2, 1);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_ENTITY_INDEX, source_index);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_ENTITY_INDEX2, target.entity_index);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_DO_NOT_ADD_SUBSPELL, 1);
            effectAPI.setEffectXData(_this->CGdEffect, effect_id, EFFECT_PHYSICAL_DAMAGE, 0);
        }

        if ((_this->CGdFigure->figures[target.entity_index].owner == -1) ||
            (_this->CGdFigure->figures[target.entity_index].flags & 10 != 0) ||
            (!toolboxAPI.isTargetable(_this->CGdFigureToolBox, target.entity_index)))
        {
            return;
        }

        uint16_t hit_chance = g_get_hit_chance(_this->AutoClass34, source_index, target.entity_index);

        // miss handling
        if ((hit_chance < spellAPI.getRandom(_this->OpaqueClass, 100)) && (param_2 == 0))
        {
            g_FUN_006c3a60(_this->AutoClass30, source_index, target.entity_index, 1, 0);
            uint16_t aggro = figureAPI.getAggroValue(_this->CGdFigure, target.entity_index, source_index);
            if (aggro < 10000)
            {
                figureAPI.setAggroValue(_this->CGdFigure, target.entity_index, source_index, 12000, 0);
            }
            uint16_t job_id = figureAPI.getJob(_this->CGdFigure, target.entity_index);

            if (isJobDoNothing(job_id))
            {
                _this->CGdFigure->figures[target.entity_index].to_do_count = 1;
                return;
            }
        }
        uint16_t damage = g_get_reduced_damage(_this->AutoClass34, source_index, target.entity_index, weapon_damage);
        damage = ((damage * param_3 + 0x32) / 100) & 0xffff;
        // glanced hit
        if (damage == 0)
        {
            uint16_t aggro = figureAPI.getAggroValue(_this->CGdFigure, target.entity_index, source_index);
            if (aggro < 10000)
            {
                figureAPI.setAggroValue(_this->CGdFigure, target.entity_index, source_index, 12000, 0);
            }
        }
        else
        {
            if (isFigureJobSpell(_this, target.entity_index))
            {
                uint16_t job_id = figureAPI.getJob(_this->CGdFigure, target.entity_index);
                if (canJobBeInterrupted(job_id))
                {
                    uint16_t chance = getAttackInterruptionChance(_this->CGdFigure, source_index, target.entity_index);
                    if (spellAPI.getRandom(_this->OpaqueClass, 100) <= chance)
                    {
                        toolboxAPI.figureSetNewJob(_this, target.entity_index, kGdJobOfferMe, 0, 0, 0);
                    }
                }
            }

            for (int i = PHASE_0; i < OnHitEnd; ++i)
            {
                std::list<std::pair<uint16_t, onhit_handler_ptr>> onhit_list = get_onhit_phase(static_cast<OnHitPhase>(i));

                uint16_t list_size = onhit_list.size();

                char ogdamage_info[128];
                snprintf(ogdamage_info, sizeof(ogdamage_info), "Before OnHit: %d", weapon_damage);
                log_info(ogdamage_info);

                int return_damage = weapon_damage;

                for (auto it = onhit_list.crbegin(); it != onhit_list.crend(); ++it)
                {
                    std::pair<uint16_t, onhit_handler_ptr> entry = *it;

                    uint16_t spell_line_id = entry.first;
                    SpellTag spell_tag = static_cast<SpellTag>(getSpellTag(spell_line_id));

                    char buffer[128];
                    snprintf(buffer, sizeof(buffer), "Found On Hit Handler: %d, %d", spell_line_id, spell_tag);
                    log_info(buffer);

                    if (spell_tag == TARGET_ONHIT_SPELL)
                    {
                        if ((_this->CGdFigure->figures[target.entity_index].flags & F_CHECK_SPELLS_BEFORE_JOB) != 0)
                        {
                            if (toolboxAPI.hasSpellOnIt(_this->CGdFigureToolBox, target.entity_index, spell_line_id))
                            {
                                onhit_handler_ptr onhit_func = entry.second;
                                return_damage = onhit_func(_this, source_index, target.entity_index, weapon_damage);
                            }
                        }
                    }
                    else
                    {
                        if ((_this->CGdFigure->figures[source_index].flags & F_CHECK_SPELLS_BEFORE_JOB) != 0)
                        {
                            if (toolboxAPI.hasSpellOnIt(_this->CGdFigureToolBox, source_index, spell_line_id))
                            {
                                onhit_handler_ptr onhit_func = entry.second;
                                return_damage = onhit_func(_this, source_index, target.entity_index, weapon_damage);
                            }
                        }
                    }
                }

                char damage_info[128];
                snprintf(damage_info, sizeof(damage_info), "OnHit: %d", return_damage);
                log_info(damage_info);

                toolboxAPI.dealDamage(_this->CGdFigureToolBox, source_index, target.entity_index, return_damage, 0, 0, 0);
                // logic here:
                //  calculate modification from spells that increase damage

                // apply set changes
                // check critical hits and riposte
                // apply
            }
        }
    }
}
