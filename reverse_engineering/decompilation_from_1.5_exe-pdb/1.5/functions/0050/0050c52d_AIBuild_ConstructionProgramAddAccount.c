/*
 * Entry: 0050c52d
 * Name: AIBuild_ConstructionProgramAddAccount
 * Namespace: Global
 * Signature: void AIBuild_ConstructionProgramAddAccount(tagCONSTRUCTION_PROGRAM * param_1, int param_2, tagCP_ACCOUNT * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AIBuild_ConstructionProgramAddAccount
          (tagCONSTRUCTION_PROGRAM *param_1,int param_2,tagCP_ACCOUNT *param_3)

{
  int iVar1;
  int iVar2;
  
  Debug_Assert((int)param_1,0xe13,".\\Schedule\\Aibuild.cpp","construction_program");
  Debug_Assert((int)param_3,0xe14,".\\Schedule\\Aibuild.cpp","account");
  Debug_Assert((uint)((uint)param_2 < 0x20),0xe15,".\\Schedule\\Aibuild.cpp",
               "(account_number >=0) && (account_number < AIBUILD_MAX_ACCOUNTS)");
  param_1->account[param_2] = param_3;
  iVar1 = 0;
  iVar2 = 0;
  if (0 < param_3->priority_levels) {
    do {
      AIBuild_PriorityLevelInit
                ((tagCP_PRIORITY_LEVEL *)((int)&param_3->priority_level->priority + iVar1));
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x10;
    } while (iVar2 < param_3->priority_levels);
  }
  return;
}
