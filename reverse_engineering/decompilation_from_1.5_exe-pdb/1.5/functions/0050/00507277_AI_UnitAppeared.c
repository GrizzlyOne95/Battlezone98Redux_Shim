/*
 * Entry: 00507277
 * Name: AI_UnitAppeared
 * Namespace: Global
 * Signature: void AI_UnitAppeared(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnitAppeared(tagUNIT *param_1)

{
  tagUNITTYPE *ptVar1;
  char *pcVar2;
  
  if (teamdata[param_1->team].aicontrol != '\0') {
    tlog_gdm("AI_UnitAdd Team %d ptr %d\n");
    param_1->autonomy = TACTAI_MEDIUM;
    param_1->tenacity = TACTAI_MEDIUM;
    param_1->selfpreservation = TACTAI_MEDIUM;
    ptVar1 = param_1->type;
    (param_1->ai).the_squad = (tag_squad *)0x0;
    (param_1->ai).cc_construct_type = 0;
    if (((uint)ptVar1->abilities & 2) == 0) {
      if ((ptVar1->resource[0].maxstored == 0) && (ptVar1->resource[1].maxstored == 0)) {
        if (param_1->movemode != MM_FIXED) {
          tlog_gdm("AI_UnitAdd (Combat)   Team %d Unit %d");
          AI_Parts_AddUnitToTeam(param_1);
          return;
        }
        pcVar2 = "AI_UnitAdd (Building Associated Unit)  Team %d Unit %d";
      }
      else {
        pcVar2 = "AI_UnitAdd (Water or Mineral transport)  Team %d Unit %d";
      }
      tlog_gdm(pcVar2);
    }
    else {
      tlog_gdm("AI_UnitAdd (CC)       Team %d Unit %d");
      AIBuild_UnassignedCCAdd(AI_map->team[param_1->team],param_1);
    }
  }
  return;
}
