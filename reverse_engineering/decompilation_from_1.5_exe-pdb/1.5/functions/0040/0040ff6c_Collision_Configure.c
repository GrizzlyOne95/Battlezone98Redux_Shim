/*
 * Entry: 0040ff6c
 * Name: Collision_Configure
 * Namespace: Global
 * Signature: int Collision_Configure(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Collision_Configure(void)

{
  void *pvVar1;
  int iVar2;
  double dVar3;
  char *pcVar4;
  int local_8;
  
  pvVar1 = IParse_New_Domain();
  local_8 = IParse_Parse_File("Collision.cfg",pvVar1);
  if (local_8 != 0) {
    return 1;
  }
  iVar2 = IParse_Get_Runtime_Int(pvVar1,"COLLISION_CONFIG_FILE_REVISION",&local_8);
  if (iVar2 < 2) {
    if (0 < iVar2) goto LAB_0040ffc3;
    pcVar4 = 
    "COLLISION AVOIDANCE CONFIGURATION: Get new \'I76\\debug\\Collision.cfg\' (%d) to synch with source code \'collision.cpp\' (%d)."
    ;
  }
  else {
    pcVar4 = 
    "COLLISION AVOIDANCE CONFIGURATION: Get new source code \'collision.cpp\' (%d) to synch with \'I76\\debug\\Collision.cfg\' (%d)"
    ;
  }
  DEBUG_systemWarning(pcVar4);
LAB_0040ffc3:
  AVOIDANCE_USING_RANGE_SEARCH =
       IParse_Get_Runtime_Int(pvVar1,"AVOIDANCE_USING_RANGE_SEARCH",&local_8);
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"GRID_X_SIZE",&local_8);
  GRID_X_SIZE = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"GRID_Z_SIZE",&local_8);
  GRID_Z_SIZE = (float)dVar3;
  COLLISION_LATERAL_REPULSION =
       IParse_Get_Runtime_Int(pvVar1,"COLLISION_LATERAL_REPULSION",&local_8);
  COLLISION_FULL_POTENTIAL_FIELD =
       IParse_Get_Runtime_Int(pvVar1,"COLLISION_FULL_POTENTIAL_FIELD",&local_8);
  COLLISION_REAL_COLLISIONS = IParse_Get_Runtime_Int(pvVar1,"COLLISION_REAL_COLLISIONS",&local_8);
  COLLISION_DIRECT_REPULSION = IParse_Get_Runtime_Int(pvVar1,"COLLISION_DIRECT_REPULSION",&local_8);
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"LATERAL_AVOIDANCE_MULTIPLIER",&local_8);
  LATERAL_AVOIDANCE_MULTIPLIER = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"LATERAL_DANGER_WIDTH",&local_8);
  LATERAL_DANGER_WIDTH = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"COLLISION_LOOK_AHEAD_TIME",&local_8);
  COLLISION_LOOK_AHEAD_TIME = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"COLLISION_SAFETY_COEFF",&local_8);
  COLLISION_SAFETY_COEFF = (float)dVar3;
  COLLISION_CHEAP_2D_COLLIDE = IParse_Get_Runtime_Int(pvVar1,"COLLISION_CHEAP_2D_COLLIDE",&local_8);
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"EXTRA_GOAL_ATTRACTION",&local_8);
  EXTRA_GOAL_ATTRACTION = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"REPULSIVE_COEFFICIENT",&local_8);
  REPULSIVE_COEFFICIENT = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"ATTRACTIVE_COEFFICIENT",&local_8);
  ATTRACTIVE_COEFFICIENT = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"DEFAULT_REPULSION_CUTOFF",&local_8);
  DEFAULT_REPULSION_CUTOFF = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"DISTANCE_OF_INFLUENCE",&local_8);
  DISTANCE_OF_INFLUENCE = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"CLIFF_REPULSION_COEFFICIENT",&local_8);
  CLIFF_REPULSION_COEFFICIENT = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"SWITCH_TO_NEXT_POINT_DISTANCE",&local_8);
  SWITCH_TO_NEXT_POINT_DISTANCE = (float)dVar3;
  dVar3 = IParse_Get_Runtime_Float(pvVar1,"EXTRA_STUCK_TIME",&local_8);
  EXTRA_STUCK_TIME = (float)dVar3;
  IParse_Trash_Domain(pvVar1);
  return 1;
}
