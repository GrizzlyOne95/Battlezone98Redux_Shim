/*
 * Entry: 005083d9
 * Name: AI_UnitRemove
 * Namespace: Global
 * Signature: void AI_UnitRemove(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnitRemove(tagUNIT *param_1)

{
  tagUNITTYPE *ptVar1;
  char *pcVar2;
  
  if ((ai_game_initialised != 0) && (teamdata[param_1->team].aicontrol != '\0')) {
    tlog_gdm("AI_UnitRemove Team %d Unit %d\n");
    ptVar1 = param_1->type;
    if (((uint)ptVar1->abilities & 2) == 0) {
      if ((ptVar1->resource[0].maxstored == 0) && (ptVar1->resource[1].maxstored == 0)) {
        if (param_1->movemode != MM_FIXED) {
          tlog_gdm("AI_UnitRemove (Combat)   Team %d Unit %d");
          AI_Parts_SubtractUnitFromTeam(param_1);
          return;
        }
        pcVar2 = "AI_UnitRemove (Building Associated Unit)   Team %d Unit %d";
      }
      else {
        pcVar2 = "AI_UnitRemove (Water or Mineral transport)  Team %d Unit %d";
      }
      tlog_gdm(pcVar2);
    }
    else {
      tlog_gdm("AI_UnitRemove (CC)       Team %d Unit %d");
      if ((param_1->ai).cc_construct_type == 0) {
        tlog_gdm("  Removing unassigned construction crew\n");
        AIBuild_UnassignedCCRemove(AI_map->team[param_1->team],param_1);
      }
      else if ((param_1->ai).cc_constructing == 0) {
        tlog_gdm("  Removing assigned construction crew - shot dead\n");
        AIBuild_ConstructionEnd((int)param_1->team,(param_1->ai).cc_construct_type);
        AIBuild_ReservedAreaRemove((int)param_1->team,(param_1->ai).cc_reserved_area);
        AI_SpentCreditRefund((int)param_1->team,(tagBUILDING *)0x0,param_1);
      }
      else {
        tlog_gdm("  Removing assigned construction crew with bldg under construction\n");
        AIBuild_ReservedAreaRemove((int)param_1->team,(param_1->ai).cc_reserved_area);
      }
    }
  }
  return;
}
