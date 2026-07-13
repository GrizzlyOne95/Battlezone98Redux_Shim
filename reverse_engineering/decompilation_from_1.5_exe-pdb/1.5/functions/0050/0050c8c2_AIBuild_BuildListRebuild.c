/*
 * Entry: 0050c8c2
 * Name: AIBuild_BuildListRebuild
 * Namespace: Global
 * Signature: void AIBuild_BuildListRebuild(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_BuildListRebuild(tag_team *param_1)

{
  int *piVar1;
  BUILD_LIST *pBVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1->aibuild).construction_program != (tagCONSTRUCTION_PROGRAM *)0x0) {
    piVar1 = &(param_1->aibuild).build_list.nodes;
    *piVar1 = 0;
    AIBuild_BuildListGenerateAccount(param_1,0);
    if (*piVar1 == 0) {
      iVar4 = (param_1->aibuild).build_list.account_first;
      iVar3 = 0x1f;
      do {
        AIBuild_BuildListGenerateAccount(param_1,iVar4);
        iVar3 = iVar3 + -1;
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x20) {
          iVar4 = 1;
        }
      } while (iVar3 != 0);
      pBVar2 = &(param_1->aibuild).build_list;
      pBVar2->account_first = pBVar2->account_first + 1;
      if ((param_1->aibuild).build_list.account_first == 0x20) {
        (param_1->aibuild).build_list.account_first = 1;
      }
    }
    (param_1->aibuild).build_list.update_required = 0;
  }
  return;
}
