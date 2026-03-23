
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0049af40(void)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  undefined4 local_8;
  
  local_8 = FUN_0069c7e0();
  local_c = FUN_0069c830("Collision.cfg",local_8);
  if (local_c == 0) {
    iVar1 = FUN_0069cb20(local_8,"COLLISION_CONFIG_FILE_REVISION",&local_c);
    if (iVar1 < 2) {
      if (iVar1 < 1) {
        FUN_007d6830("COLLISION AVOIDANCE CONFIGURATION: Get new \'bzone\\Collision.cfg\' (%d) to synch with source code \'collision.cpp\' (%d)."
                     ,iVar1,1);
      }
    }
    else {
      FUN_007d6830("COLLISION AVOIDANCE CONFIGURATION: Get new source code \'collision.cpp\' (%d) to synch with \'bzone\\Collision.cfg\' (%d)"
                   ,1,iVar1);
    }
    _DAT_008e795c = FUN_0069cb20(local_8,"AVOIDANCE_USING_RANGE_SEARCH",&local_c);
    fVar2 = (float10)FUN_0069cc40(local_8,"GRID_X_SIZE",&local_c);
    _DAT_008e7970 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"GRID_Z_SIZE",&local_c);
    _DAT_008e7960 = (float)fVar2;
    DAT_008e7930 = FUN_0069cb20(local_8,"COLLISION_LATERAL_REPULSION",&local_c);
    _DAT_008e7974 = FUN_0069cb20(local_8,"COLLISION_FULL_POTENTIAL_FIELD",&local_c);
    DAT_008e793c = FUN_0069cb20(local_8,"COLLISION_REAL_COLLISIONS",&local_c);
    DAT_008e7940 = FUN_0069cb20(local_8,"COLLISION_DIRECT_REPULSION",&local_c);
    fVar2 = (float10)FUN_0069cc40(local_8,"LATERAL_AVOIDANCE_MULTIPLIER",&local_c);
    _DAT_008e7950 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"LATERAL_DANGER_WIDTH",&local_c);
    DAT_008e794c = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"COLLISION_LOOK_AHEAD_TIME",&local_c);
    DAT_008e7934 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"COLLISION_SAFETY_COEFF",&local_c);
    _DAT_008e7938 = (float)fVar2;
    DAT_009173d8 = FUN_0069cb20(local_8,"COLLISION_CHEAP_2D_COLLIDE",&local_c);
    fVar2 = (float10)FUN_0069cc40(local_8,"EXTRA_GOAL_ATTRACTION",&local_c);
    _DAT_008e796c = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"REPULSIVE_COEFFICIENT",&local_c);
    _DAT_008e792c = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"ATTRACTIVE_COEFFICIENT",&local_c);
    _DAT_008e7968 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"DEFAULT_REPULSION_CUTOFF",&local_c);
    DAT_008e7948 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"DISTANCE_OF_INFLUENCE",&local_c);
    _DAT_008e7958 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"CLIFF_REPULSION_COEFFICIENT",&local_c);
    _DAT_008e7954 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"SWITCH_TO_NEXT_POINT_DISTANCE",&local_c);
    DAT_008e7944 = (float)fVar2;
    fVar2 = (float10)FUN_0069cc40(local_8,"EXTRA_STUCK_TIME",&local_c);
    _DAT_008e7964 = (float)fVar2;
    FUN_0069ca90(local_8);
  }
  return 1;
}

