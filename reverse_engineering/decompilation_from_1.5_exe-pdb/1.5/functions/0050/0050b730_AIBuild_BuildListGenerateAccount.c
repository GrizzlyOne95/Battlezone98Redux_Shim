/*
 * Entry: 0050b730
 * Name: AIBuild_BuildListGenerateAccount
 * Namespace: Global
 * Signature: void AIBuild_BuildListGenerateAccount(tag_team * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_BuildListGenerateAccount(tag_team *param_1,int param_2)

{
  tagCP_ACCOUNT *ptVar1;
  tagCP_BUILD_TYPE tVar2;
  tag_team *ptVar3;
  int iVar4;
  tagCP_PRIORITY_LEVEL *ptVar5;
  int iVar6;
  
  iVar4 = param_2;
  ptVar3 = param_1;
  ptVar1 = ((param_1->aibuild).construction_program)->account[param_2];
  if (ptVar1 != (tagCP_ACCOUNT *)0x0) {
    param_1 = (tag_team *)0x0;
    param_2 = 0;
    do {
      ptVar5 = (tagCP_PRIORITY_LEVEL *)((int)&ptVar1->priority_level->priority + param_2);
      tVar2 = ptVar5->build_type;
      if (tVar2 == NUMBER_TO_HAVE) {
        iVar6 = AIBuildListGeneratePriorityLevel_NUMBER_TO_HAVE(ptVar3,ptVar5,iVar4);
      }
      else if (tVar2 == NUMBER_TO_BUILD) {
        iVar6 = AIBuildListGeneratePriorityLevel_NUMBER_TO_BUILD(ptVar3,ptVar5,iVar4);
      }
      else if (tVar2 == RATIO_TO_BUILD) {
        iVar6 = AIBuildListGeneratePriorityLevel_RATIO_TO_BUILD(ptVar3,ptVar5,iVar4);
      }
      else if (tVar2 == RATIO_TO_HAVE) {
        iVar6 = AIBuildListGeneratePriorityLevel_RATIO_TO_HAVE(ptVar3,ptVar5,iVar4);
      }
      else {
        tlog(1,"Error in ai construction account #%d, priority level #%d illegal build type is %d\n"
            );
        iVar6 = 0;
      }
      param_1 = (tag_team *)((int)&param_1->team_ID + 1);
      param_2 = param_2 + 0x10;
    } while ((iVar6 == 0) && ((int)param_1 < ptVar1->priority_levels));
  }
  return;
}
