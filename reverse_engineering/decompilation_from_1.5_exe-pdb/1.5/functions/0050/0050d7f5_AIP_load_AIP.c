/*
 * Entry: 0050d7f5
 * Name: AIP_load_AIP
 * Namespace: Global
 * Signature: tagAIP_struct * AIP_load_AIP(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagAIP_struct * __cdecl AIP_load_AIP(char *param_1)

{
  char cVar1;
  void *pvVar2;
  tagAIP_struct *ptVar3;
  int *piVar4;
  char *pcVar5;
  int iVar6;
  double dVar8;
  int local_8;
  int iVar7;
  
  tlog_ild("loading aip");
  pvVar2 = IParse_New_Domain();
  if (tinfo.workdir[0] != '\0') {
    IParse_Append_Path(pvVar2,tinfo.workdir);
  }
  local_8 = IParse_Parse_File(param_1,pvVar2);
  tlog_ild("AIP file parsed");
  if (local_8 == 10) {
    tlog_ild("AIP file \'%s\' not found\n");
    ptVar3 = (tagAIP_struct *)0x0;
  }
  else {
    ptVar3 = calloc(1,0x568);
    piVar4 = calloc(0x20,4);
    ptVar3->budget = piVar4;
    piVar4 = calloc(0x20,4);
    ptVar3->max_reserve = piVar4;
    pcVar5 = param_1;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    iVar6 = (int)pcVar5 - (int)(param_1 + 1);
    do {
      iVar7 = iVar6;
      iVar6 = iVar7 + -1;
      if (iVar6 < 0) break;
    } while (param_1[iVar6] != '\\');
    pcVar5 = param_1 + iVar7;
    iVar6 = 0x438 - (int)pcVar5;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)ptVar3 + iVar6] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"VERBOSE_SCHEDULER",&local_8);
    ptVar3->VERBOSE_SCHEDULER = iVar6;
    if (local_8 != 0) {
      ptVar3->VERBOSE_SCHEDULER = 0;
    }
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"escort_priority",&local_8);
    ptVar3->escort_priority = iVar6;
    if (local_8 != 0) {
      ptVar3->escort_priority = 15000;
    }
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"min_escort_force",&local_8);
    ptVar3->min_escort_force = iVar6;
    if (local_8 != 0) {
      ptVar3->min_escort_force = 1;
    }
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"max_escort_force",&local_8);
    ptVar3->max_escort_force = iVar6;
    if (local_8 != 0) {
      ptVar3->max_escort_force = 1;
    }
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"ground_unit_threat",&local_8);
    ptVar3->ground_unit_threat = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"threat_priority",&local_8);
    ptVar3->threat_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"distance_priority",&local_8);
    ptVar3->distance_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"defend_buildings_priority",&local_8);
    ptVar3->defend_buildings_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"perimeter_priority",&local_8);
    ptVar3->perimeter_priority = iVar6;
    ptVar3->appropriateness_priority = 1;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"persistence_priority",&local_8);
    ptVar3->persistence_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"exploration_priority",&local_8);
    ptVar3->exploration_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"scripted_priority",&local_8);
    ptVar3->scripted_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"attack_enemy_base_priority",&local_8);
    ptVar3->attack_enemy_base_priority = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"relaxation_cycles",&local_8);
    ptVar3->relaxation_cycles = iVar6;
    dVar8 = IParse_Get_Runtime_Float(pvVar2,"relaxation_coefficient",&local_8);
    ptVar3->relaxation_coefficient = (float)dVar8;
    ptVar3->tactical_ai = TACTAI_LOW;
    dVar8 = IParse_Get_Runtime_Double(pvVar2,"max_matching_force_ratio",&local_8);
    ptVar3->max_matching_force_ratio = dVar8;
    dVar8 = IParse_Get_Runtime_Double(pvVar2,"min_matching_force_ratio",&local_8);
    ptVar3->min_matching_force_ratio = dVar8;
    dVar8 = IParse_Get_Runtime_Double(pvVar2,"generic_ground_ratio",&local_8);
    ptVar3->generic_ground_ratio = dVar8;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"max_building_defense_force",&local_8);
    ptVar3->max_building_defense_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"min_building_defense_force",&local_8);
    ptVar3->min_building_defense_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"max_exploration_force",&local_8);
    ptVar3->max_exploration_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"min_exploration_force",&local_8);
    ptVar3->min_exploration_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"max_perimeter_force",&local_8);
    ptVar3->max_perimeter_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"min_perimeter_force",&local_8);
    ptVar3->min_perimeter_force = iVar6;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"recompute_strategy_period",&local_8);
    ptVar3->recompute_strategy_period = iVar6;
    ptVar3->last_strategy_unitcycles = -1 - iVar6;
    piVar4 = ptVar3->max_goals_of_type;
    for (iVar6 = 0xb; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar4 = -1;
      piVar4 = piVar4 + 1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_DEFEND_BASE_GOALS",&local_8);
    ptVar3->max_goals_of_type[1] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[1] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_ATTACK_TROOPS_GOALS",&local_8);
    ptVar3->max_goals_of_type[2] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[2] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_SEIGE_GOALS",&local_8);
    ptVar3->max_goals_of_type[3] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[3] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_EXPLORATION_GOALS",&local_8);
    ptVar3->max_goals_of_type[4] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[4] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_SCRIPTED_GOALS",&local_8);
    ptVar3->max_goals_of_type[5] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[5] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_PERIMETER_GOALS",&local_8);
    ptVar3->max_goals_of_type[6] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[6] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_RECON_GOAL_GOALS",&local_8);
    ptVar3->max_goals_of_type[7] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[7] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_RESOURCE_GOAL_GOALS",&local_8);
    ptVar3->max_goals_of_type[8] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[8] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_OTHER_GOAL_GOALS",&local_8);
    ptVar3->max_goals_of_type[9] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[9] = -1;
    }
    local_8 = -0x11;
    iVar6 = IParse_Get_Runtime_Int(pvVar2,"MAX_ESCORT_GOAL_GOALS",&local_8);
    ptVar3->max_goals_of_type[10] = iVar6;
    if (local_8 != 0) {
      ptVar3->max_goals_of_type[10] = -1;
    }
    AIP_Load_UCP(pvVar2,ptVar3);
    AIP_Load_Force_Matching(pvVar2,ptVar3);
    AIP_Load_Building_Matching(pvVar2,ptVar3);
    IParse_Trash_Domain(pvVar2);
  }
  return ptVar3;
}
