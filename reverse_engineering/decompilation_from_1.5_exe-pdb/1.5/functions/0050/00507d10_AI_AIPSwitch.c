/*
 * Entry: 00507d10
 * Name: AI_AIPSwitch
 * Namespace: Global
 * Signature: void AI_AIPSwitch(int param_1, tagAIP_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_AIPSwitch(int param_1,tagAIP_struct *param_2)

{
  tlog_gdm("AIPSwitch %d to %0x\n");
  AI_Team_Assign_AIP(AI_map->team[param_1],param_2);
  tlog_gdm("AIPSwitch over\n");
  return;
}
