/*
 * Entry: 0050c3e8
 * Name: AIBuild_TeamExecuteConstructionProgram
 * Namespace: Global
 * Signature: void AIBuild_TeamExecuteConstructionProgram(tag_team * param_1, tagCONSTRUCTION_PROGRAM * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AIBuild_TeamExecuteConstructionProgram(tag_team *param_1,tagCONSTRUCTION_PROGRAM *param_2)

{
  Debug_Assert((int)param_1,0xd6d,".\\Schedule\\Aibuild.cpp","the_team");
  Debug_Assert((int)param_2,0xd6e,".\\Schedule\\Aibuild.cpp","construction_program");
  (param_1->aibuild).construction_program = param_2;
  return;
}
