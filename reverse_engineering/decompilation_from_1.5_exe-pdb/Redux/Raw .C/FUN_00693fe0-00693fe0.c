
void * FUN_00693fe0(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined4 uVar4;
  char *pcVar5;
  float10 fVar6;
  char *local_28;
  int local_24;
  char *local_20;
  char *local_1c;
  int local_18;
  int local_10;
  void *local_c;
  char local_6;
  char local_5;
  
  FUN_006a6030("loading aip");
  uVar2 = FUN_0069c7e0();
  if (DAT_00936157 != '\0') {
    FUN_0069d0f0(uVar2,&DAT_00936157);
  }
  local_10 = FUN_0069c830(param_1,uVar2);
  FUN_006a6030("AIP file parsed");
  if (local_10 == 10) {
    FUN_006a6030("AIP file \'%s\' not found\n",param_1);
    local_c = (void *)0x0;
  }
  else {
    local_c = malloc(0x568);
    pvVar3 = calloc(0x20,4);
    *(void **)((int)local_c + 0x90) = pvVar3;
    pvVar3 = calloc(0x20,4);
    *(void **)((int)local_c + 0x94) = pvVar3;
    local_1c = param_1;
    do {
      local_6 = *local_1c;
      local_1c = local_1c + 1;
    } while (local_6 != '\0');
    local_18 = (int)local_1c - (int)(param_1 + 1);
    do {
      iVar1 = local_18;
      local_18 = iVar1 + -1;
      if ((local_18 < 0) || (param_1[local_18] == '\\')) break;
    } while (param_1[local_18] != '/');
    local_28 = param_1 + iVar1;
    pcVar5 = (char *)((int)local_c + 0x438);
    local_20 = pcVar5;
    do {
      local_5 = *local_28;
      *local_20 = local_5;
      local_28 = local_28 + 1;
      local_20 = local_20 + 1;
    } while (local_5 != '\0');
    uVar4 = FUN_0069cb20(uVar2,"VERBOSE_SCHEDULER",&local_10,pcVar5);
    *(undefined4 *)((int)local_c + 0x408) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x408) = 0;
    }
    uVar4 = FUN_0069cb20(uVar2,"escort_priority",&local_10,pcVar5);
    *(undefined4 *)((int)local_c + 0x30) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x30) = 15000;
    }
    uVar4 = FUN_0069cb20(uVar2,"min_escort_force",&local_10);
    *(undefined4 *)((int)local_c + 0x34) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x34) = 1;
    }
    uVar4 = FUN_0069cb20(uVar2,"max_escort_force",&local_10);
    *(undefined4 *)((int)local_c + 0x38) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x38) = 1;
    }
    uVar4 = FUN_0069cb20(uVar2,"ground_unit_threat",&local_10);
    *(undefined4 *)((int)local_c + 4) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"threat_priority",&local_10);
    *(undefined4 *)((int)local_c + 8) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"distance_priority",&local_10);
    *(undefined4 *)((int)local_c + 0xc) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"defend_buildings_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x14) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"perimeter_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x28) = uVar4;
    *(undefined4 *)((int)local_c + 0x10) = 1;
    uVar4 = FUN_0069cb20(uVar2,"persistence_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x1c) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"exploration_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x20) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"scripted_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x24) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"attack_enemy_base_priority",&local_10);
    *(undefined4 *)((int)local_c + 0x18) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"relaxation_cycles",&local_10);
    *(undefined4 *)((int)local_c + 0x78) = uVar4;
    fVar6 = (float10)FUN_0069cc40(uVar2,"relaxation_coefficient",&local_10);
    *(float *)((int)local_c + 0x7c) = (float)fVar6;
    *(undefined4 *)((int)local_c + 0x80) = 0;
    fVar6 = (float10)FUN_0069cd40(uVar2,"max_matching_force_ratio",&local_10);
    *(double *)((int)local_c + 0x40) = (double)fVar6;
    fVar6 = (float10)FUN_0069cd40(uVar2,"min_matching_force_ratio",&local_10);
    *(double *)((int)local_c + 0x48) = (double)fVar6;
    fVar6 = (float10)FUN_0069cd40(uVar2,"generic_ground_ratio",&local_10);
    *(double *)((int)local_c + 0x50) = (double)fVar6;
    uVar4 = FUN_0069cb20(uVar2,"max_building_defense_force",&local_10);
    *(undefined4 *)((int)local_c + 0x60) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"min_building_defense_force",&local_10);
    *(undefined4 *)((int)local_c + 100) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"max_exploration_force",&local_10);
    *(undefined4 *)((int)local_c + 0x6c) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"min_exploration_force",&local_10);
    *(undefined4 *)((int)local_c + 0x68) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"max_perimeter_force",&local_10);
    *(undefined4 *)((int)local_c + 0x5c) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"min_perimeter_force",&local_10);
    *(undefined4 *)((int)local_c + 0x58) = uVar4;
    uVar4 = FUN_0069cb20(uVar2,"recompute_strategy_period",&local_10);
    *(undefined4 *)((int)local_c + 0x84) = uVar4;
    *(int *)((int)local_c + 0x88) = -(*(int *)((int)local_c + 0x84) + 1);
    for (local_24 = 0; local_24 < 0xb; local_24 = local_24 + 1) {
      *(undefined4 *)((int)local_c + local_24 * 4 + 0x40c) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_DEFEND_BASE_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x410) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x410) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_ATTACK_TROOPS_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x414) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x414) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_SEIGE_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x418) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x418) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_EXPLORATION_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x41c) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x41c) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_SCRIPTED_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x420) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x420) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_PERIMETER_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x424) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x424) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_RECON_GOAL_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x428) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x428) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_RESOURCE_GOAL_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x42c) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x42c) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_OTHER_GOAL_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x430) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x430) = 0xffffffff;
    }
    local_10 = -0x11;
    uVar4 = FUN_0069cb20(uVar2,"MAX_ESCORT_GOAL_GOALS",&local_10);
    *(undefined4 *)((int)local_c + 0x434) = uVar4;
    if (local_10 != 0) {
      *(undefined4 *)((int)local_c + 0x434) = 0xffffffff;
    }
    FUN_00693900(uVar2,local_c);
    FUN_00693b20(uVar2,local_c);
    FUN_00693d50(uVar2,local_c);
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
              (uVar2,local_c);
    FUN_0069ca90(uVar2);
  }
  return local_c;
}

