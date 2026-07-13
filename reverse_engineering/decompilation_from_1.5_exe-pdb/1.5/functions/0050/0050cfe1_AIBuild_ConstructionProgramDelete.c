/*
 * Entry: 0050cfe1
 * Name: AIBuild_ConstructionProgramDelete
 * Namespace: Global
 * Signature: void AIBuild_ConstructionProgramDelete(tagCONSTRUCTION_PROGRAM * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionProgramDelete(tagCONSTRUCTION_PROGRAM *param_1)

{
  int iVar1;
  
  Debug_Assert((int)param_1,0xdde,".\\Schedule\\Aibuild.cpp","construction_program");
  iVar1 = 0;
  do {
    if (param_1->account[iVar1] != (tagCP_ACCOUNT *)0x0) {
      AIBuild_AccountDelete(param_1->account[iVar1]);
      param_1->account[iVar1] = (tagCP_ACCOUNT *)0x0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x20);
  free(param_1);
  return;
}
