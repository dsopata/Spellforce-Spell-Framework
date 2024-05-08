#include "sf_spelleffect_handlers.h"
#include "sf_utility.h"
#include "sf_spelleffect_registry.h"

handler_ptr effect_ability_benefactions_handler;
handler_ptr effect_ability_berserk_handler;
handler_ptr effect_ability_boons_handler;
handler_ptr effect_ability_critical_hits_handler;
handler_ptr effect_ability_durability_handler;
handler_ptr effect_ability_endurance_handler;
handler_ptr effect_ability_patronize_handler;
handler_ptr effect_ability_riposte_handler;
handler_ptr effect_ability_salvo_handler;
handler_ptr effect_ability_shelter_handler;
handler_ptr effect_ability_shift_life_handler;
handler_ptr effect_ability_steelskin_handler;
handler_ptr effect_ability_trueshot_handler;
handler_ptr effect_ability_warcy_handler;
handler_ptr effect_acid_cloud_handler;
handler_ptr effect_almightiness_black_handler;
handler_ptr effect_almightiness_elemental_handler;
handler_ptr effect_almightiness_elemental2_handler;
handler_ptr effect_almightiness_mental_handler;
handler_ptr effect_almightiness_white_handler;
handler_ptr effect_amok_handler;
handler_ptr effect_tower_arrow_handler;
handler_ptr effect_assistance_handler;
handler_ptr effect_aura_handler;
handler_ptr effect_befriend_handler;
handler_ptr effect_unknown1_handler;
handler_ptr effect_blizzard_handler;
handler_ptr effect_brilliance_handler;
handler_ptr effect_cannibalize_handler;
handler_ptr effect_chain_handler;
handler_ptr effect_charisma_handler;
handler_ptr effect_charm_handler;
handler_ptr effect_charm_animal_handler;
handler_ptr effect_chill_resistance_handler;
handler_ptr effect_confuse_handler;
handler_ptr effect_confuse_area_handler;
handler_ptr effect_conservation_handler;
handler_ptr effect_cure_disease_handler;
handler_ptr effect_cure_poison_handler;
handler_ptr effect_dark_banishing_handler;
handler_ptr effect_darkness_area_handler;
handler_ptr effect_death_handler;
handler_ptr effect_death_grasp_handler;
handler_ptr effect_decay_handler;
handler_ptr effect_decay2_handler;
handler_ptr effect_demoralization_handler;
handler_ptr effect_detect_magic_handler;
handler_ptr effect_detect_metal_handler;
handler_ptr effect_dexterity_handler;
handler_ptr effect_disenchant_handler;
handler_ptr effect_dispel_black_aura_handler;
handler_ptr effect_dispel_white_aura_handler;
handler_ptr effect_disrupt_handler;
handler_ptr effect_distract_handler;
handler_ptr effect_dominate_break_handler;
handler_ptr effect_dominate_handler;
handler_ptr effect_dominate_animal_handler;
handler_ptr effect_dominate_undead_handler;
handler_ptr effect_endurance_handler;
handler_ptr effect_enlightement_handler;
handler_ptr effect_essence_black_handler;
handler_ptr effect_essence_elemental_handler;
handler_ptr effect_essence_elemental2_handler;
handler_ptr effect_essence_mental_handler;
handler_ptr effect_essence_white_handler;
handler_ptr effect_eternity_handler;
handler_ptr effect_extinct_handler;
handler_ptr effect_tower_extinct_handler;
handler_ptr effect_fake_spell_one_figure_handler;
handler_ptr effect_fast_fighting_handler;
handler_ptr effect_feet_of_clay_handler;
handler_ptr effect_feign_death_handler;
handler_ptr effect_fireball1_handler;
handler_ptr effect_fireball2_handler;
handler_ptr effect_firebullet_handler;
handler_ptr effect_fireburst_handler;
handler_ptr effect_fire_resistance_handler;
handler_ptr effect_fireshield1_handler;
handler_ptr effect_fireshield2_handler;
handler_ptr effect_flexibility_handler;
handler_ptr effect_flexibility_area_handler;
handler_ptr effect_fog_handler;
handler_ptr effect_forget_handler;
handler_ptr effect_freeze_handler;
handler_ptr effect_freeze_area_handler;
handler_ptr effect_guard_handler;
handler_ptr effect_hallow_handler;
handler_ptr effect_healing_handler;
handler_ptr effect_healing_area_handler;
handler_ptr effect_unknown2_handler;
handler_ptr effect_healing_aura_handler;
handler_ptr effect_holy_touch_handler;
handler_ptr effect_iceshield_handler;
handler_ptr effect_hypnotize_area_handler;
handler_ptr effect_hypnotize_handler;
handler_ptr effect_ice1_handler;
handler_ptr effect_ice2_handler;
handler_ptr effect_icestrike1_handler;
handler_ptr effect_iceshield2_handler;
handler_ptr effect_iceshield3_handler;
handler_ptr effect_icestrike2_handler;
handler_ptr effect_illuminate_handler;
handler_ptr effect_inability_handler;
handler_ptr effect_inflexibility_handler;
handler_ptr effect_inflexibility_area_handler;
handler_ptr effect_invisibility_handler;
handler_ptr effect_invulnerability_handler;
handler_ptr effect_lifetap_handler;
handler_ptr effect_lifetap_aura_handler;
handler_ptr effect_manadrain_handler;
handler_ptr effect_manashield_handler;
handler_ptr effect_manatap_handler;
handler_ptr effect_manatap_aura_handler;
handler_ptr effect_meditation_handler;
handler_ptr effect_melt_resistance_handler;
handler_ptr effect_mirage_handler;
handler_ptr effect_mutation_handler;
handler_ptr effect_pain_handler;
handler_ptr effect_pain_area_handler;
handler_ptr effect_tower_pain_handler;
handler_ptr effect_pestilence_handler;
handler_ptr effect_petrify_handler;
handler_ptr effect_plague_area_handler;
handler_ptr effect_poison_handler;
handler_ptr effect_cloak_of_nor_handler;
handler_ptr effect_quickness_handler;
handler_ptr effect_quickness_area_handler;
handler_ptr effect_rain_of_fire_handler;
handler_ptr effect_raise_dead_handler;
handler_ptr effect_regenerate_handler;
handler_ptr effect_reinforcement_handler;
handler_ptr effect_remediless_handler;
handler_ptr effect_remove_curse_handler;
handler_ptr effect_retention_handler;
handler_ptr effect_revenge_handler;
handler_ptr effect_rock_bullet_handler;
handler_ptr effect_roots_handler;
handler_ptr effect_roots_area_handler;
handler_ptr effect_sacrifice_mana_handler;
handler_ptr effect_self_illusion_handler;
handler_ptr effect_sentinel_healing_handler;
handler_ptr effect_shift_mana_handler;
handler_ptr effect_shock_handler;
handler_ptr effect_shockwave_handler;
handler_ptr effect_slow_fighting_handler;
handler_ptr effect_slowness_handler;
handler_ptr effect_slowness_area_handler;
handler_ptr effect_spark_handler;
handler_ptr effect_stone_handler;
handler_ptr effect_rain_of_stone_handler;
handler_ptr effect_tower_stone_handler;
handler_ptr effect_strength_handler;
handler_ptr effect_strength_area_handler;
handler_ptr effect_suffocation_handler;
handler_ptr effect_suicide_death_handler;
handler_ptr effect_suicide_heal_handler;
handler_ptr effect_summon_handler;
handler_ptr effect_thornshield_handler;
handler_ptr effect_thorns_handler;
handler_ptr effect_torture_handler;
handler_ptr effect_feedback_handler;
handler_ptr effect_wave_handler;
handler_ptr effect_weaken_handler;
handler_ptr effect_weaken_area_handler;

void initEffectHandlers()
{
    effect_ability_benefactions_handler = (handler_ptr)(ASI::AddrOf(0x32c090));
    effect_ability_berserk_handler = (handler_ptr)(ASI::AddrOf(0x32c4a0));
    effect_ability_boons_handler = (handler_ptr)(ASI::AddrOf(0x32c670));
    effect_ability_critical_hits_handler = (handler_ptr)(ASI::AddrOf(0x32c810));
    effect_ability_durability_handler = (handler_ptr)(ASI::AddrOf(0x32c9c0));
    effect_ability_endurance_handler = (handler_ptr)(ASI::AddrOf(0x32cb90));
    effect_ability_patronize_handler = (handler_ptr)(ASI::AddrOf(0x32cf60));
    effect_ability_riposte_handler = (handler_ptr)(ASI::AddrOf(0x32d330));
    effect_ability_salvo_handler = (handler_ptr)(ASI::AddrOf(0x32d4e0));
    effect_ability_shelter_handler = (handler_ptr)(ASI::AddrOf(0x32d6b0));
    effect_ability_shift_life_handler = (handler_ptr)(ASI::AddrOf(0x32d880));
    effect_ability_steelskin_handler = (handler_ptr)(ASI::AddrOf(0x32dbf0));
    effect_ability_trueshot_handler = (handler_ptr)(ASI::AddrOf(0x32ddc0));
    effect_ability_warcy_handler = (handler_ptr)(ASI::AddrOf(0x32df90));
    effect_acid_cloud_handler = (handler_ptr)(ASI::AddrOf(0x32e370));
    effect_almightiness_black_handler = (handler_ptr)(ASI::AddrOf(0x32e730));
    effect_almightiness_elemental_handler = (handler_ptr)(ASI::AddrOf(0x32e9d0));
    effect_almightiness_elemental2_handler = (handler_ptr)(ASI::AddrOf(0x32eca0));
    effect_almightiness_mental_handler = (handler_ptr)(ASI::AddrOf(0x32f050));
    effect_almightiness_white_handler = (handler_ptr)(ASI::AddrOf(0x32f330));
    effect_amok_handler = (handler_ptr)(ASI::AddrOf(0x32f590));
    effect_tower_arrow_handler = (handler_ptr)(ASI::AddrOf(0x32f840));
    effect_assistance_handler = (handler_ptr)(ASI::AddrOf(0x32fbc0));
    effect_aura_handler = (handler_ptr)(ASI::AddrOf(0x32fd40));
    effect_befriend_handler = (handler_ptr)(ASI::AddrOf(0x3309b0));
    effect_unknown1_handler = (handler_ptr)(ASI::AddrOf(0x330bc0));
    effect_blizzard_handler = (handler_ptr)(ASI::AddrOf(0x330e00));
    effect_brilliance_handler = (handler_ptr)(ASI::AddrOf(0x331190));
    effect_cannibalize_handler = (handler_ptr)(ASI::AddrOf(0x3313a0));
    effect_chain_handler = (handler_ptr)(ASI::AddrOf(0x331510));
    effect_charisma_handler = (handler_ptr)(ASI::AddrOf(0x331bf0));
    effect_charm_handler = (handler_ptr)(ASI::AddrOf(0x331dc0));
    effect_charm_animal_handler = (handler_ptr)(ASI::AddrOf(0x332280));
    effect_chill_resistance_handler = (handler_ptr)(ASI::AddrOf(0x332750));
    effect_confuse_handler = (handler_ptr)(ASI::AddrOf(0x3329a0));
    effect_confuse_area_handler = (handler_ptr)(ASI::AddrOf(0x332c30));
    effect_conservation_handler = (handler_ptr)(ASI::AddrOf(0x333130));
    effect_cure_disease_handler = (handler_ptr)(ASI::AddrOf(0x333360));
    effect_cure_poison_handler = (handler_ptr)(ASI::AddrOf(0x333560));
    effect_dark_banishing_handler = (handler_ptr)(ASI::AddrOf(0x333760));
    effect_darkness_area_handler = (handler_ptr)(ASI::AddrOf(0x3339b0));
    effect_death_handler = (handler_ptr)(ASI::AddrOf(0x333db0));
    effect_death_grasp_handler = (handler_ptr)(ASI::AddrOf(0x333fc0));
    effect_decay_handler = (handler_ptr)(ASI::AddrOf(0x334150));
    effect_decay2_handler = (handler_ptr)(ASI::AddrOf(0x334390));
    effect_demoralization_handler = (handler_ptr)(ASI::AddrOf(0x334760));
    effect_detect_magic_handler = (handler_ptr)(ASI::AddrOf(0x334a20));
    effect_detect_metal_handler = (handler_ptr)(ASI::AddrOf(0x334cb0));
    effect_dexterity_handler = (handler_ptr)(ASI::AddrOf(0x334f30));
    effect_disenchant_handler = (handler_ptr)(ASI::AddrOf(0x335180));
    effect_dispel_black_aura_handler = (handler_ptr)(ASI::AddrOf(0x3353d0));
    effect_dispel_white_aura_handler = (handler_ptr)(ASI::AddrOf(0x335680));
    effect_disrupt_handler = (handler_ptr)(ASI::AddrOf(0x335930));
    effect_distract_handler = (handler_ptr)(ASI::AddrOf(0x335c30));
    effect_dominate_break_handler = (handler_ptr)(ASI::AddrOf(0x335f40));
    effect_dominate_handler = (handler_ptr)(ASI::AddrOf(0x336060));
    effect_dominate_animal_handler = (handler_ptr)(ASI::AddrOf(0x336500));
    effect_dominate_undead_handler = (handler_ptr)(ASI::AddrOf(0x336a10));
    effect_endurance_handler = (handler_ptr)(ASI::AddrOf(0x336e40));
    effect_enlightement_handler = (handler_ptr)(ASI::AddrOf(0x3370f0));
    effect_essence_black_handler = (handler_ptr)(ASI::AddrOf(0x337450));
    effect_essence_elemental_handler = (handler_ptr)(ASI::AddrOf(0x3376f0));
    effect_essence_elemental2_handler = (handler_ptr)(ASI::AddrOf(0x3379c0));
    effect_essence_mental_handler = (handler_ptr)(ASI::AddrOf(0x337d20));
    effect_essence_white_handler = (handler_ptr)(ASI::AddrOf(0x338000));
    effect_eternity_handler = (handler_ptr)(ASI::AddrOf(0x338260));
    effect_extinct_handler = (handler_ptr)(ASI::AddrOf(0x338670));
    effect_tower_extinct_handler = (handler_ptr)(ASI::AddrOf(0x338a50));
    effect_fake_spell_one_figure_handler = (handler_ptr)(ASI::AddrOf(0x338e00));
    effect_fast_fighting_handler = (handler_ptr)(ASI::AddrOf(0x338e90));
    effect_feet_of_clay_handler = (handler_ptr)(ASI::AddrOf(0x3390e0));
    effect_feign_death_handler = (handler_ptr)(ASI::AddrOf(0x339590));
    effect_fireball1_handler = (handler_ptr)(ASI::AddrOf(0x339750));
    effect_fireball2_handler = (handler_ptr)(ASI::AddrOf(0x339a20));
    effect_firebullet_handler = (handler_ptr)(ASI::AddrOf(0x339e00));
    effect_fireburst_handler = (handler_ptr)(ASI::AddrOf(0x339fc0));
    effect_fire_resistance_handler = (handler_ptr)(ASI::AddrOf(0x33a3e0));
    effect_fireshield1_handler = (handler_ptr)(ASI::AddrOf(0x33a610));
    effect_fireshield2_handler = (handler_ptr)(ASI::AddrOf(0x33a7b0));
    effect_flexibility_handler = (handler_ptr)(ASI::AddrOf(0x33a970));
    effect_flexibility_area_handler = (handler_ptr)(ASI::AddrOf(0x33abc0));
    effect_fog_handler = (handler_ptr)(ASI::AddrOf(0x33aef0));
    effect_forget_handler = (handler_ptr)(ASI::AddrOf(0x33b240));
    effect_freeze_handler = (handler_ptr)(ASI::AddrOf(0x33b4b0));
    effect_freeze_area_handler = (handler_ptr)(ASI::AddrOf(0x33b740));
    effect_guard_handler = (handler_ptr)(ASI::AddrOf(0x33bad0));
    effect_hallow_handler = (handler_ptr)(ASI::AddrOf(0x33bc60));
    effect_healing_handler = (handler_ptr)(ASI::AddrOf(0x33c070));
    effect_healing_area_handler = (handler_ptr)(ASI::AddrOf(0x33c250));
    effect_unknown2_handler = (handler_ptr)(ASI::AddrOf(0x33c5f0));
    effect_healing_aura_handler = (handler_ptr)(ASI::AddrOf(0x33c770));
    effect_holy_touch_handler = (handler_ptr)(ASI::AddrOf(0x33c8c0));
    effect_iceshield_handler = (handler_ptr)(ASI::AddrOf(0x33c980));
    effect_hypnotize_area_handler = (handler_ptr)(ASI::AddrOf(0x33cd90));
    effect_hypnotize_handler = (handler_ptr)(ASI::AddrOf(0x33d3f0));
    effect_ice1_handler = (handler_ptr)(ASI::AddrOf(0x33d7d0));
    effect_ice2_handler = (handler_ptr)(ASI::AddrOf(0x33da90));
    effect_icestrike1_handler = (handler_ptr)(ASI::AddrOf(0x33dd50));
    effect_iceshield2_handler = (handler_ptr)(ASI::AddrOf(0x33e210));
    effect_iceshield3_handler = (handler_ptr)(ASI::AddrOf(0x33e3b0));
    effect_icestrike2_handler = (handler_ptr)(ASI::AddrOf(0x33e620));
    effect_illuminate_handler = (handler_ptr)(ASI::AddrOf(0x33ea50));
    effect_inability_handler = (handler_ptr)(ASI::AddrOf(0x33ed50));
    effect_inflexibility_handler = (handler_ptr)(ASI::AddrOf(0x33ef50));
    effect_inflexibility_area_handler = (handler_ptr)(ASI::AddrOf(0x33f150));
    effect_invisibility_handler = (handler_ptr)(ASI::AddrOf(0x33f530));
    effect_invulnerability_handler = (handler_ptr)(ASI::AddrOf(0x33f7d0));
    effect_lifetap_handler = (handler_ptr)(ASI::AddrOf(0x33f990));
    effect_lifetap_aura_handler = (handler_ptr)(ASI::AddrOf(0x33fbf0));
    effect_manadrain_handler = (handler_ptr)(ASI::AddrOf(0x33fdf0));
    effect_manashield_handler = (handler_ptr)(ASI::AddrOf(0x340000));
    effect_manatap_handler = (handler_ptr)(ASI::AddrOf(0x3401a0));
    effect_manatap_aura_handler = (handler_ptr)(ASI::AddrOf(0x3403d0));
    effect_meditation_handler = (handler_ptr)(ASI::AddrOf(0x340600));
    effect_melt_resistance_handler = (handler_ptr)(ASI::AddrOf(0x3406d0));
    effect_mirage_handler = (handler_ptr)(ASI::AddrOf(0x340920));
    effect_mutation_handler = (handler_ptr)(ASI::AddrOf(0x340e60));
    effect_pain_handler = (handler_ptr)(ASI::AddrOf(0x3418c0));
    effect_pain_area_handler = (handler_ptr)(ASI::AddrOf(0x341af0));
    effect_tower_pain_handler = (handler_ptr)(ASI::AddrOf(0x341e90));
    effect_pestilence_handler = (handler_ptr)(ASI::AddrOf(0x342060));
    effect_petrify_handler = (handler_ptr)(ASI::AddrOf(0x342440));
    effect_plague_area_handler = (handler_ptr)(ASI::AddrOf(0x342700));
    effect_poison_handler = (handler_ptr)(ASI::AddrOf(0x342be0));
    effect_cloak_of_nor_handler = (handler_ptr)(ASI::AddrOf(0x343020));
    effect_quickness_handler = (handler_ptr)(ASI::AddrOf(0x3431b0));
    effect_quickness_area_handler = (handler_ptr)(ASI::AddrOf(0x343400));
    effect_rain_of_fire_handler = (handler_ptr)(ASI::AddrOf(0x343730));
    effect_raise_dead_handler = (handler_ptr)(ASI::AddrOf(0x343ac0));
    effect_regenerate_handler = (handler_ptr)(ASI::AddrOf(0x343f60));
    effect_reinforcement_handler = (handler_ptr)(ASI::AddrOf(0x344170));
    effect_remediless_handler = (handler_ptr)(ASI::AddrOf(0x344750));
    effect_remove_curse_handler = (handler_ptr)(ASI::AddrOf(0x3449a0));
    effect_retention_handler = (handler_ptr)(ASI::AddrOf(0x344bb0));
    effect_revenge_handler = (handler_ptr)(ASI::AddrOf(0x344dc0));
    effect_rock_bullet_handler = (handler_ptr)(ASI::AddrOf(0x3453f0));
    effect_roots_handler = (handler_ptr)(ASI::AddrOf(0x345880));
    effect_roots_area_handler = (handler_ptr)(ASI::AddrOf(0x345c60));
    effect_sacrifice_mana_handler = (handler_ptr)(ASI::AddrOf(0x346240));
    effect_self_illusion_handler = (handler_ptr)(ASI::AddrOf(0x3463c0));
    effect_sentinel_healing_handler = (handler_ptr)(ASI::AddrOf(0x346ab0));
    effect_shift_mana_handler = (handler_ptr)(ASI::AddrOf(0x346f70));
    effect_shock_handler = (handler_ptr)(ASI::AddrOf(0x347310));
    effect_shockwave_handler = (handler_ptr)(ASI::AddrOf(0x347580));
    effect_slow_fighting_handler = (handler_ptr)(ASI::AddrOf(0x347980));
    effect_slowness_handler = (handler_ptr)(ASI::AddrOf(0x347b80));
    effect_slowness_area_handler = (handler_ptr)(ASI::AddrOf(0x347dd0));
    effect_spark_handler = (handler_ptr)(ASI::AddrOf(0x3481a0));
    effect_stone_handler = (handler_ptr)(ASI::AddrOf(0x348530));
    effect_rain_of_stone_handler = (handler_ptr)(ASI::AddrOf(0x348640));
    effect_tower_stone_handler = (handler_ptr)(ASI::AddrOf(0x3489d0));
    effect_strength_handler = (handler_ptr)(ASI::AddrOf(0x348db0));
    effect_strength_area_handler = (handler_ptr)(ASI::AddrOf(0x349000));
    effect_suffocation_handler = (handler_ptr)(ASI::AddrOf(0x349330));
    effect_suicide_death_handler = (handler_ptr)(ASI::AddrOf(0x349570));
    effect_suicide_heal_handler = (handler_ptr)(ASI::AddrOf(0x3497a0));
    effect_summon_handler = (handler_ptr)(ASI::AddrOf(0x3499b0));
    effect_thornshield_handler = (handler_ptr)(ASI::AddrOf(0x349bb0));
    effect_thorns_handler = (handler_ptr)(ASI::AddrOf(0x349d70));
    effect_torture_handler = (handler_ptr)(ASI::AddrOf(0x349f40));
    effect_feedback_handler = (handler_ptr)(ASI::AddrOf(0x34a3f0));
    effect_wave_handler = (handler_ptr)(ASI::AddrOf(0x34a5a0));
    effect_weaken_handler = (handler_ptr)(ASI::AddrOf(0x34aa10));
    effect_weaken_area_handler = (handler_ptr)(ASI::AddrOf(0x34ac60));

    registerEffectHandler(1, effect_fireburst_handler);
    registerEffectHandler(2, effect_healing_handler);
    registerEffectHandler(3, effect_death_handler);
    registerEffectHandler(4, effect_poison_handler);
    registerEffectHandler(5, effect_cure_poison_handler);
    registerEffectHandler(6, effect_invulnerability_handler);
    registerEffectHandler(7, effect_unknown1_handler);
    registerEffectHandler(8, effect_icestrike1_handler);
    registerEffectHandler(9, effect_fog_handler);
    registerEffectHandler(10, effect_stone_handler);
    registerEffectHandler(0xb, effect_slowness_handler);
    registerEffectHandler(0xc, effect_freeze_handler);
    registerEffectHandler(0xd, effect_decay_handler);
    registerEffectHandler(0xe, effect_pain_handler);
    registerEffectHandler(0xf, effect_iceshield_handler);
    registerEffectHandler(0x10, effect_illuminate_handler);
    registerEffectHandler(0x11, effect_fireball1_handler);
    registerEffectHandler(0x12, effect_fireshield1_handler);
    registerEffectHandler(0x13, effect_iceshield2_handler);
    registerEffectHandler(0x14, effect_lifetap_handler);
    registerEffectHandler(0x15, effect_decay2_handler);
    registerEffectHandler(0x16, effect_iceshield3_handler);
    registerEffectHandler(0x17, effect_summon_handler);
    registerEffectHandler(0x18, effect_petrify_handler);
    registerEffectHandler(0x19, effect_pestilence_handler);
    registerEffectHandler(0x1a, effect_cure_disease_handler);
    registerEffectHandler(0x1b, effect_pain_area_handler);
    registerEffectHandler(0x1c, effect_death_grasp_handler);
    registerEffectHandler(0x1d, effect_inflexibility_handler);
    registerEffectHandler(0x1e, effect_detect_magic_handler);
    registerEffectHandler(0x1f, effect_weaken_handler);
    registerEffectHandler(0x20, effect_dark_banishing_handler);
    registerEffectHandler(0x21, effect_slowness_area_handler);
    registerEffectHandler(0x22, effect_inflexibility_area_handler);
    registerEffectHandler(0x23, effect_weaken_area_handler);
    registerEffectHandler(0x24, effect_plague_area_handler);
    registerEffectHandler(0x25, effect_remediless_handler);
    registerEffectHandler(0x26, effect_healing_area_handler);
    registerEffectHandler(0x27, effect_sentinel_healing_handler);
    registerEffectHandler(0x28, effect_quickness_handler);
    registerEffectHandler(0x29, effect_quickness_area_handler);
    registerEffectHandler(0x2a, effect_thornshield_handler);
    registerEffectHandler(0x2b, effect_flexibility_handler);
    registerEffectHandler(0x2c, effect_flexibility_area_handler);
    registerEffectHandler(0x2d, effect_strength_handler);
    registerEffectHandler(0x2e, effect_strength_area_handler);
    registerEffectHandler(0x2f, effect_guard_handler);
    registerEffectHandler(0x30, effect_regenerate_handler);
    registerEffectHandler(0x31, effect_hallow_handler);
    registerEffectHandler(0x32, effect_fireshield2_handler);
    registerEffectHandler(0x33, effect_thorns_handler);
    registerEffectHandler(0x34, effect_raise_dead_handler);
    registerEffectHandler(0x37, effect_forget_handler);
    registerEffectHandler(0x38, effect_retention_handler);
    registerEffectHandler(0x39, effect_brilliance_handler);
    registerEffectHandler(0x3a, effect_sacrifice_mana_handler);
    registerEffectHandler(0x3b, effect_manatap_handler);
    registerEffectHandler(0x3c, effect_manadrain_handler);
    registerEffectHandler(0x3d, effect_amok_handler);
    registerEffectHandler(0x3e, effect_confuse_handler);
    registerEffectHandler(0x3f, effect_disrupt_handler);
    registerEffectHandler(0x40, effect_acid_cloud_handler);
    registerEffectHandler(0x41, effect_rain_of_fire_handler);
    registerEffectHandler(0x42, effect_shock_handler);
    registerEffectHandler(0x43, effect_blizzard_handler);
    registerEffectHandler(0x44, effect_rain_of_stone_handler);
    registerEffectHandler(0x45, effect_charm_animal_handler);
    registerEffectHandler(0x46, effect_invisibility_handler);
    registerEffectHandler(0x47, effect_extinct_handler);
    registerEffectHandler(0x48, effect_remove_curse_handler);
    registerEffectHandler(0x49, effect_aura_handler);
    registerEffectHandler(0x4a, effect_suffocation_handler);
    registerEffectHandler(0x4b, effect_slow_fighting_handler);
    registerEffectHandler(0x4c, effect_inability_handler);
    registerEffectHandler(0x4d, effect_suicide_death_handler);
    registerEffectHandler(0x4e, effect_endurance_handler);
    registerEffectHandler(0x4f, effect_fast_fighting_handler);
    registerEffectHandler(0x50, effect_dexterity_handler);
    registerEffectHandler(0x51, effect_suicide_heal_handler);
    registerEffectHandler(0x52, effect_dispel_white_aura_handler);
    registerEffectHandler(0x53, effect_dispel_black_aura_handler);
    registerEffectHandler(0x54, effect_dominate_animal_handler);
    registerEffectHandler(0x55, effect_wave_handler);
    registerEffectHandler(0x56, effect_rock_bullet_handler);
    registerEffectHandler(0x57, effect_melt_resistance_handler);
    registerEffectHandler(0x58, effect_chill_resistance_handler);
    registerEffectHandler(0x59, effect_charisma_handler);
    registerEffectHandler(0x5a, effect_enlightement_handler);
    registerEffectHandler(0x5b, effect_meditation_handler);
    registerEffectHandler(0x5c, effect_shockwave_handler);
    registerEffectHandler(0x5d, effect_befriend_handler);
    registerEffectHandler(0x5e, effect_dominate_handler);
    registerEffectHandler(0x5f, effect_charm_handler);
    registerEffectHandler(0x60, effect_tower_arrow_handler);
    registerEffectHandler(0x61, effect_healing_aura_handler);
    registerEffectHandler(0x62, effect_icestrike2_handler);
    registerEffectHandler(99, effect_distract_handler);
    registerEffectHandler(100, effect_detect_metal_handler);
    registerEffectHandler(0x65, effect_conservation_handler)
    registerEffectHandler(0x66, effect_lifetap_aura_handler)
    registerEffectHandler(0x67, effect_fireball2_handler)
    registerEffectHandler(0x68, effect_self_illusion_handler)
    registerEffectHandler(0x69, effect_ability_warcy_handler)
    registerEffectHandler(0x6a, effect_ability_benefactions_handler)
    registerEffectHandler(0x6b, effect_ability_patronize_handler)
    registerEffectHandler(0x6c, effect_ability_endurance_handler)
    registerEffectHandler(0x6d, effect_ability_berserk_handler)
    registerEffectHandler(0x6e, effect_ability_boons_handler)
    registerEffectHandler(0x6f, effect_ability_shelter_handler)
    registerEffectHandler(0x70, effect_ability_durability_handler)
    registerEffectHandler(0x71, effect_ability_trueshot_handler)
    registerEffectHandler(0x72, effect_ability_steelskin_handler)
    registerEffectHandler(0x73, effect_ability_salvo_handler)
    registerEffectHandler(0x74, effect_spark_handler)
    registerEffectHandler(0x75, effect_demoralization_handler)
    registerEffectHandler(0x76, effect_hypnotize_handler)
    registerEffectHandler(0x77, effect_tower_pain_handler)
    registerEffectHandler(0x78, effect_tower_stone_handler)
    registerEffectHandler(0x79, effect_cloak_of_nor_handler)
    registerEffectHandler(0x7a, effect_feign_death_handler)
    registerEffectHandler(0x7b, effect_dominate_break_handler)
    registerEffectHandler(0x7c, effect_disenchant_handler)
    registerEffectHandler(0x7d, effect_unknown2_handler)
    registerEffectHandler(0x7e, effect_ice1_handler)
    registerEffectHandler(0x7f, effect_ice2_handler)
    registerEffectHandler(0x80, effect_firebullet_handler)
    registerEffectHandler(0x81, effect_tower_extinct_handler)
    registerEffectHandler(0x82, effect_manatap_aura_handler)
    registerEffectHandler(0x83, effect_fire_resistance_handler)
    registerEffectHandler(0x84, effect_essence_black_handler)
    registerEffectHandler(0x85, effect_almightiness_black_handler)
    registerEffectHandler(0x86, effect_essence_white_handler)
    registerEffectHandler(0x87, effect_almightiness_white_handler)
    registerEffectHandler(0x88, effect_essence_elemental_handler)
    registerEffectHandler(0x89, effect_almightiness_elemental_handler)
    registerEffectHandler(0x8a, effect_essence_mental_handler)
    registerEffectHandler(0x8b, effect_almightiness_mental_handler)
    registerEffectHandler(0x8c, effect_essence_elemental2_handler)
    registerEffectHandler(0x8d, effect_almightiness_elemental2_handler)
    registerEffectHandler(0x8e, effect_assistance_handler)
    registerEffectHandler(0x8f, effect_holy_touch_handler)
    registerEffectHandler(0x90, effect_roots_area_handler)
    registerEffectHandler(0x91, effect_eternity_handler)
    registerEffectHandler(0x92, effect_cannibalize_handler)
    registerEffectHandler(0x93, effect_dominate_undead_handler)
    registerEffectHandler(0x94, effect_darkness_area_handler)
    registerEffectHandler(0x95, effect_freeze_area_handler)
    registerEffectHandler(0x96, effect_shift_mana_handler)
    registerEffectHandler(0x97, effect_revenge_handler)
    registerEffectHandler(0x98, effect_torture_handler)
    registerEffectHandler(0x99, effect_reinforcement_handler)
    registerEffectHandler(0x9a, effect_hypnotize_area_handler)
    registerEffectHandler(0x9b, effect_feet_of_clay_handler)
    registerEffectHandler(0x9c, effect_confuse_area_handler)
    registerEffectHandler(0x9d, effect_mutation_handler)
    registerEffectHandler(0x9e, effect_ability_shift_life_handler)
    registerEffectHandler(0x9f, effect_ability_riposte_handler)
    registerEffectHandler(0xa0, effect_ability_critical_hits_handler)
    registerEffectHandler(0xa1, effect_manashield_handler)
    registerEffectHandler(0xa2, effect_chain_handler)
    registerEffectHandler(0xa3, effect_roots_handler)
    registerEffectHandler(0xa4, effect_mirage_handler)
    registerEffectHandler(0xa5, effect_fake_spell_one_figure_handler)
    registerEffectHandler(0xa6, effect_feedback_handler)
}


