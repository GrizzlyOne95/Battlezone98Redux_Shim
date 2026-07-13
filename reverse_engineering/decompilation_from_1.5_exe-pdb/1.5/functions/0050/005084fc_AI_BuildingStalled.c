/*
 * Entry: 005084fc
 * Name: AI_BuildingStalled
 * Namespace: Global
 * Signature: void AI_BuildingStalled(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingStalled(tagUNIT *param_1)

{
  tag_team *ptVar1;
  
  if (teamdata[param_1->team].aicontrol != '\0') {
    ptVar1 = AI_map->team[param_1->team];
    tlog_gdm("AI_BuildingStalled Team %d ptr %d\n");
    AIBuild_ConstructionEnd((int)param_1->team,(param_1->ai).cc_construct_type);
    AIBuild_ReservedAreaRemove((int)param_1->team,(param_1->ai).cc_reserved_area);
    AI_SpentCreditRefund((int)param_1->team,(tagBUILDING *)0x0,param_1);
    AIBuild_UnassignedCCAdd(ptVar1,param_1);
    Units_SOrderStop(param_1);
    (param_1->ai).cc_construct_type = 0;
    (param_1->ai).cc_construct_cost = 0;
    (param_1->ai).cc_constructing = 0;
    (param_1->ai).cc_account = 0;
    (param_1->ai).cc_reserved_area = 0;
  }
  return;
}
