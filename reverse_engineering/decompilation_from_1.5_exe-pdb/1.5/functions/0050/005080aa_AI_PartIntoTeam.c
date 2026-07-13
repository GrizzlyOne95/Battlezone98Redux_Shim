/*
 * Entry: 005080aa
 * Name: AI_PartIntoTeam
 * Namespace: Global
 * Signature: void AI_PartIntoTeam(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_PartIntoTeam(tagUNIT *param_1)

{
  int iVar1;
  
  tlog_gdm("AI   Team %d Unit %d");
  iVar1 = AI_IsSpecialForce(param_1);
  if (iVar1 == 0) {
    AI_UnitAppeared(param_1);
  }
  else {
    tlog_gdm("AI_PartIntoTeam: Special Force Unit %d ignored\n");
  }
  return;
}
