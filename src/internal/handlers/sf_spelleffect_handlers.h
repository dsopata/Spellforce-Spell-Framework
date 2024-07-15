#ifndef SF_SPELLEFFECT_HANDLER_H
#define SF_SPELLEFFECT_HANDLER_H

#include "../../api/sfsf.h"
#include "../../asi/sf_asi.h"

void initialize_vanilla_effect_handler_hooks();

extern handler_ptr effect_ability_benefactions_handler;
extern handler_ptr effect_ability_berserk_handler;
extern handler_ptr effect_ability_boons_handler;
extern handler_ptr effect_ability_critical_hits_handler;
extern handler_ptr effect_ability_durability_handler;
extern handler_ptr effect_ability_endurance_handler;
extern handler_ptr effect_ability_patronize_handler;
extern handler_ptr effect_ability_riposte_handler;
extern handler_ptr effect_ability_salvo_handler;
extern handler_ptr effect_ability_shelter_handler;
extern handler_ptr effect_ability_shift_life_handler;
extern handler_ptr effect_ability_steelskin_handler;
extern handler_ptr effect_ability_trueshot_handler;
extern handler_ptr effect_ability_warcy_handler;
extern handler_ptr effect_acid_cloud_handler;
extern handler_ptr effect_almightiness_black_handler;
extern handler_ptr effect_almightiness_elemental_handler;
extern handler_ptr effect_almightiness_elemental2_handler;
extern handler_ptr effect_almightiness_mental_handler;
extern handler_ptr effect_almightiness_white_handler;
extern handler_ptr effect_amok_handler;
extern handler_ptr effect_tower_arrow_handler;
extern handler_ptr effect_assistance_handler;
extern handler_ptr effect_aura_handler;
extern handler_ptr effect_befriend_handler;
extern handler_ptr effect_unknown1_handler;
extern handler_ptr effect_blizzard_handler;
extern handler_ptr effect_brilliance_handler;
extern handler_ptr effect_cannibalize_handler;
extern handler_ptr effect_chain_handler;
extern handler_ptr effect_charisma_handler;
extern handler_ptr effect_charm_handler;
extern handler_ptr effect_charm_animal_handler;
extern handler_ptr effect_chill_resistance_handler;
extern handler_ptr effect_confuse_handler;
extern handler_ptr effect_confuse_area_handler;
extern handler_ptr effect_conservation_handler;
extern handler_ptr effect_cure_disease_handler;
extern handler_ptr effect_cure_poison_handler;
extern handler_ptr effect_dark_banishing_handler;
extern handler_ptr effect_darkness_area_handler;
extern handler_ptr effect_death_handler;
extern handler_ptr effect_death_grasp_handler;
extern handler_ptr effect_decay_handler;
extern handler_ptr effect_decay2_handler;
extern handler_ptr effect_demoralization_handler;
extern handler_ptr effect_detect_magic_handler;
extern handler_ptr effect_detect_metal_handler;
extern handler_ptr effect_dexterity_handler;
extern handler_ptr effect_disenchant_handler;
extern handler_ptr effect_dispel_black_aura_handler;
extern handler_ptr effect_dispel_white_aura_handler;
extern handler_ptr effect_disrupt_handler;
extern handler_ptr effect_distract_handler;
extern handler_ptr effect_dominate_break_handler;
extern handler_ptr effect_dominate_handler;
extern handler_ptr effect_dominate_animal_handler;
extern handler_ptr effect_dominate_undead_handler;
extern handler_ptr effect_endurance_handler;
extern handler_ptr effect_enlightement_handler;
extern handler_ptr effect_essence_black_handler;
extern handler_ptr effect_essence_elemental_handler;
extern handler_ptr effect_essence_elemental2_handler;
extern handler_ptr effect_essence_mental_handler;
extern handler_ptr effect_essence_white_handler;
extern handler_ptr effect_eternity_handler;
extern handler_ptr effect_extinct_handler;
extern handler_ptr effect_tower_extinct_handler;
extern handler_ptr effect_fake_spell_one_figure_handler;
extern handler_ptr effect_fast_fighting_handler;
extern handler_ptr effect_feet_of_clay_handler;
extern handler_ptr effect_feign_death_handler;
extern handler_ptr effect_fireball1_handler;
extern handler_ptr effect_fireball2_handler;
extern handler_ptr effect_firebullet_handler;
extern handler_ptr effect_fireburst_handler;
extern handler_ptr effect_fire_resistance_handler;
extern handler_ptr effect_fireshield1_handler;
extern handler_ptr effect_fireshield2_handler;
extern handler_ptr effect_flexibility_handler;
extern handler_ptr effect_flexibility_area_handler;
extern handler_ptr effect_fog_handler;
extern handler_ptr effect_forget_handler;
extern handler_ptr effect_freeze_handler;
extern handler_ptr effect_freeze_area_handler;
extern handler_ptr effect_guard_handler;
extern handler_ptr effect_hallow_handler;
extern handler_ptr effect_healing_handler;
extern handler_ptr effect_healing_area_handler;
extern handler_ptr effect_unknown2_handler;
extern handler_ptr effect_healing_aura_handler;
extern handler_ptr effect_holy_touch_handler;
extern handler_ptr effect_iceshield_handler;
extern handler_ptr effect_hypnotize_area_handler;
extern handler_ptr effect_hypnotize_handler;
extern handler_ptr effect_ice1_handler;
extern handler_ptr effect_ice2_handler;
extern handler_ptr effect_icestrike1_handler;
extern handler_ptr effect_iceshield2_handler;
extern handler_ptr effect_iceshield3_handler;
extern handler_ptr effect_icestrike2_handler;
extern handler_ptr effect_illuminate_handler;
extern handler_ptr effect_inability_handler;
extern handler_ptr effect_inflexibility_handler;
extern handler_ptr effect_inflexibility_area_handler;
extern handler_ptr effect_invisibility_handler;
extern handler_ptr effect_invulnerability_handler;
extern handler_ptr effect_lifetap_handler;
extern handler_ptr effect_lifetap_aura_handler;
extern handler_ptr effect_manadrain_handler;
extern handler_ptr effect_manashield_handler;
extern handler_ptr effect_manatap_handler;
extern handler_ptr effect_manatap_aura_handler;
extern handler_ptr effect_meditation_handler;
extern handler_ptr effect_melt_resistance_handler;
extern handler_ptr effect_mirage_handler;
extern handler_ptr effect_mutation_handler;
extern handler_ptr effect_pain_handler;
extern handler_ptr effect_pain_area_handler;
extern handler_ptr effect_tower_pain_handler;
extern handler_ptr effect_pestilence_handler;
extern handler_ptr effect_petrify_handler;
extern handler_ptr effect_plague_area_handler;
extern handler_ptr effect_poison_handler;
extern handler_ptr effect_cloak_of_nor_handler;
extern handler_ptr effect_quickness_handler;
extern handler_ptr effect_quickness_area_handler;
extern handler_ptr effect_rain_of_fire_handler;
extern handler_ptr effect_raise_dead_handler;
extern handler_ptr effect_regenerate_handler;
extern handler_ptr effect_reinforcement_handler;
extern handler_ptr effect_remediless_handler;
extern handler_ptr effect_remove_curse_handler;
extern handler_ptr effect_retention_handler;
extern handler_ptr effect_revenge_handler;
extern handler_ptr effect_rock_bullet_handler;
extern handler_ptr effect_roots_handler;
extern handler_ptr effect_roots_area_handler;
extern handler_ptr effect_sacrifice_mana_handler;
extern handler_ptr effect_self_illusion_handler;
extern handler_ptr effect_sentinel_healing_handler;
extern handler_ptr effect_shift_mana_handler;
extern handler_ptr effect_shock_handler;
extern handler_ptr effect_shockwave_handler;
extern handler_ptr effect_slow_fighting_handler;
extern handler_ptr effect_slowness_handler;
extern handler_ptr effect_slowness_area_handler;
extern handler_ptr effect_spark_handler;
extern handler_ptr effect_stone_handler;
extern handler_ptr effect_rain_of_stone_handler;
extern handler_ptr effect_tower_stone_handler;
extern handler_ptr effect_strength_handler;
extern handler_ptr effect_strength_area_handler;
extern handler_ptr effect_suffocation_handler;
extern handler_ptr effect_suicide_death_handler;
extern handler_ptr effect_suicide_heal_handler;
extern handler_ptr effect_summon_handler;
extern handler_ptr effect_thornshield_handler;
extern handler_ptr effect_thorns_handler;
extern handler_ptr effect_torture_handler;
extern handler_ptr effect_feedback_handler;
extern handler_ptr effect_wave_handler;
extern handler_ptr effect_weaken_handler;
extern handler_ptr effect_weaken_area_handler;

#endif