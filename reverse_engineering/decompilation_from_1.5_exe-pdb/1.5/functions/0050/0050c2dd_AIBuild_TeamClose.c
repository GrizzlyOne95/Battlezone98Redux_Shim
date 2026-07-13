/*
 * Entry: 0050c2dd
 * Name: AIBuild_TeamClose
 * Namespace: Global
 * Signature: void AIBuild_TeamClose(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamClose(tag_team *param_1)

{
  Debug_Assert((int)param_1,0xd18,".\\Schedule\\Aibuild.cpp","the_team");
  (param_1->aibuild).construction_program = (tagCONSTRUCTION_PROGRAM *)0x0;
  AIBuild_ConstructionDelete(param_1->team_ID);
  AIBuild_UnassignedCCClose(param_1);
  return;
}
