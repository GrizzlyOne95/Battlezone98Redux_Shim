/*
 * Entry: 00508dbe
 * Name: AI_Team_Assign_AIP
 * Namespace: Global
 * Signature: void AI_Team_Assign_AIP(tag_team * param_1, tagAIP_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_Assign_AIP(tag_team *param_1,tagAIP_struct *param_2)

{
  if (param_1->AIP != (tagAIP_struct *)0x0) {
    AIBuild_TeamClearConstructionProgram(param_1);
  }
  param_1->AIP = param_2;
  AIBuild_Budget(param_1,param_2->budget,param_2->max_reserve);
  AIBuild_TeamExecuteConstructionProgram(param_1,param_1->AIP->the_construction_program);
  AI_Match_Team_Unit_Strength_Recalculate(param_1);
  return;
}
