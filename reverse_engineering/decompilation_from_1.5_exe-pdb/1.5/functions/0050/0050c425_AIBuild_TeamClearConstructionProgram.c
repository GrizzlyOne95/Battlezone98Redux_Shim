/*
 * Entry: 0050c425
 * Name: AIBuild_TeamClearConstructionProgram
 * Namespace: Global
 * Signature: void AIBuild_TeamClearConstructionProgram(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamClearConstructionProgram(tag_team *param_1)

{
  Debug_Assert((int)param_1,0xd7b,".\\Schedule\\Aibuild.cpp","the_team");
  (param_1->aibuild).construction_program = (tagCONSTRUCTION_PROGRAM *)0x0;
  return;
}
