#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "sf_general_structures.h"

typedef enum
{
    SPELL_TICK_COUNT_AUX = 0x05,
    SPELL_TICK_COUNT = 0x12,
    SPELL_DOUBLE_DAMAGE = 0x26,
    SPELL_TARGET = 0x33,
    SPELL_PESTILENCE_DAMAGE = 0x0E,
    EFFECT_EFFECT_INDEX = 0x06,
    SPELL_STAT_MUL_MODIFIER = 0x0A,
    SPELL_STAT_MUL_MODIFIER2 = 0x27,
    SPELL_STAT_MUL_MODIFIER3 = 0x2B,
    SPELL_STAT_MUL_MODIFIER4 = 0x2C,
    SPELL_CONSERVATION_SHIELD = 0x0B
} SpellDataKey;

typedef enum
{
    CHECK_SPELLS_BEFORE_CHECK_BATTLE,
    CHECK_SPELLS_BEFORE_JOB2,
    UNFREEZE
} SpellFlagKey;

typedef enum
{
    kGdEffectNone = 0,
    kGdEffectSpellCast = 1,
    kGdEffectSpellHitWorld = 2,
    kGdEffectSpellHitTarget = 3,
    kGdEffectSpellDOTHitTarget = 4,
    kGdEffectSpellMissTarget = 5,
    kGdEffectSpellResolve = 6,
    kGdEffectSummonWorker = 7,
    kGdEffectWorkerAppears = 8,
    kGdEffectSummonHero = 9,
    kGdEffectHeroAppears = 10,
    kGdEffectSpellTargetResisted = 11,
    kGdEffectSpellResolveSelf = 12,
    kGdEffectMeteorFall = 13,
    kGdEffectMeteorHit = 14,
    kGdEffectBlizzardFall = 15,
    kGdEffectBlizzardHit = 16,
    kGdEffectStoneFall = 17,
    kGdEffectStoneHit = 18,
    kGdEffectPetAppears = 19,
    kGdEffectTest = 20,
    kGdEffectMonumentClaimed = 21,
    kGdEffectMonumentWorking = 22,
    kGdEffectAuraResolve = 23,
    kGdEffectProjectile = 24,
    kGdEffectBuilding = 25,
    kGdEffectPlayerBind = 26,
    kGdEffectSummonMainChar = 27,
    kGdEffectMainCharAppears = 28,
    kGdEffectTitanProduction = 29,
    kGdEffectTitanAppears = 30,
    kGdEffectMentalTowerCast = 31,
    kGdEffectMentalTowerIdle = 32,
    kGdEffectMonumentBullet = 33,
    kGdEffectMonumentHitFigure = 34,
    kGdEffectSpellAssistanceHitFigure = 35,
    kGdEffectChainResolve = 36,
    kGdEffectSpellVoodooHitFigure = 37,
    kGdEffectSpellManaShieldHitFigure = 38,
    kGdEffectMax = 39
} CGdEffectType;

typedef struct __attribute__((packed))
{
    uint16_t spell_id;
    uint16_t spell_line_id;
    uint8_t skill_requirements[12];
    uint16_t mana_cost;
    uint32_t cast_time;
    uint32_t recast_time;
    uint16_t min_range;
    uint16_t max_range;
    uint8_t cast_type1;
    uint8_t cast_type2;
    uint32_t params[10];
    uint16_t effect_power;
    uint16_t effect_range;
} SF_CGdResourceSpell;

// Declare the function pointers for the SpellFunctions group
DECLARE_FUNCTION(void, setXData, SF_CGdSpell *_this, uint16_t spell_id, uint8_t xdatakey, uint32_t value);
DECLARE_FUNCTION(void, initializeSpellData, SF_CGdSpell *_this, uint16_t spell_id, SpellDataKey key);
DECLARE_FUNCTION(void, setEffectDone, SF_CGdSpell *_this, uint16_t spell_id, uint16_t param_2);
DECLARE_FUNCTION(uint32_t, addToXData, SF_CGdSpell *_this, uint16_t spell_id, SpellDataKey key, uint32_t value);
DECLARE_FUNCTION(uint32_t, getChanceToResistSpell, void *autoclass34, uint16_t source, uint16_t target, SF_SpellEffectInfo effect_info);
DECLARE_FUNCTION(uint16_t, getRandom, void *autoclass14, uint16_t max_value);
DECLARE_FUNCTION(void, addVisualEffect, SF_CGdSpell *_this, uint16_t spell_id, CGdEffectType effect_id, void *unused, SF_CGdTargetData *target, uint32_t tick_start, uint16_t tick_count, void *corner_coords);
DECLARE_FUNCTION(void, figureAggro, SF_CGdSpell *_this, uint16_t spell_id, uint16_t target_index);
DECLARE_FUNCTION(SF_CGdResourceSpell *, getResourceSpellData, void *, SF_CGdResourceSpell *spellData, uint16_t index);
DECLARE_FUNCTION(uint32_t, getXData, SF_CGdSpell *_this, uint16_t spell_id, SpellDataKey key);
DECLARE_FUNCTION(SF_Rectangle *, getTargetsRectangle, SF_CGdSpell *_this, SF_Rectangle *output, uint16_t spell_id, uint16_t radius, SF_Coord *center_maybe);
DECLARE_FUNCTION(void, removeDLLNode, SF_CGdSpell *_this, uint16_t param_1);
DECLARE_FUNCTION(void, spellClearFigureFlag, SF_CGdSpell *_this, uint16_t spell_id, SpellFlagKey key);
DECLARE_FUNCTION(void, onSpellRemove, SF_CGdFigure *_this, uint16_t spell_id);

DECLARE_FUNCTION(void, figClrChkSplBfrChkBattle, SF_CGdSpell *_this, uint16_t spell_id, uint16_t unk1);
DECLARE_FUNCTION(void, figTryClrCHkSPlBfrJob2, SF_CGdSpell *_this, uint16_t spell_id, uint16_t unk1);
DECLARE_FUNCTION(void, figTryUnfreeze, SF_CGdSpell *_this, uint16_t spell_id, uint16_t unk1);

DECLARE_FUNCTION_GROUP(Spell,
                       setXData_ptr setXData;
                       initializeSpellData_ptr initializeSpellData;
                       setEffectDone_ptr setEffectDone;
                       addToXData_ptr addToXData;
                       getChanceToResistSpell_ptr getChanceToResistSpell;
                       getRandom_ptr getRandom;
                       getResourceSpellData_ptr getResourceSpellData;
                       addVisualEffect_ptr addVisualEffect;
                       figureAggro_ptr figureAggro;
                       getXData_ptr getXData;
                       getTargetsRectangle_ptr getTargetsRectangle;
                       removeDLLNode_ptr removeDLLNode;
                       spellClearFigureFlag_ptr spellClearFigureFlag;
                       onSpellRemove_ptr onSpellRemove;

                       // flag clear function used inside spellClearFigureFlag Wrapper
                       figClrChkSplBfrChkBattle_ptr figClrChkSplBfrChkBattle;
                       figTryClrCHkSPlBfrJob2_ptr figTryClrCHkSPlBfrJob2;
                       figTryUnfreeze_ptr figTryUnfreeze;);