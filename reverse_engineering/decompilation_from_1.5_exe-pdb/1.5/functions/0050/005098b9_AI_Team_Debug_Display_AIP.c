/*
 * Entry: 005098b9
 * Name: AI_Team_Debug_Display_AIP
 * Namespace: Global
 * Signature: void AI_Team_Debug_Display_AIP(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_Team_Debug_Display_AIP(tag_team *param_1)

{
  char local_d0 [88];
  undefined1 local_78 [112];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  DebCons_PutString("AIP Parameters:");
  DebCons_PutString("---------------");
  sprintf(local_d0,"Threat:              %d",param_1->AIP->threat_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Distance:            %d",param_1->AIP->distance_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Defend Base:         %d",param_1->AIP->defend_buildings_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Defend Perimeter:    %d",param_1->AIP->perimeter_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Attack Enemy Base:   %d",param_1->AIP->attack_enemy_base_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Persistence:         %d",param_1->AIP->persistence_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Exploration:         %d",param_1->AIP->exploration_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Scripted:            %d",param_1->AIP->scripted_priority);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Match:    %lf-> %lf",param_1->AIP->min_matching_force_ratio,
          param_1->AIP->max_matching_force_ratio);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Defend Forces: %d->%d",param_1->AIP->min_building_defense_force,
          param_1->AIP->max_building_defense_force);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Perimeter Frc: %d->%d",param_1->AIP->min_perimeter_force,
          param_1->AIP->max_building_defense_force);
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Explore Force: %d->%d");
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Cycles, Coeff: %d, %f");
  DebCons_PutString(local_d0);
  sprintf(local_d0,"Recompute:           %d cycles",param_1->AIP->recompute_strategy_period);
  DebCons_PutString(local_d0);
  DebCons_PutString(param_1->AIP->name);
  return;
}
