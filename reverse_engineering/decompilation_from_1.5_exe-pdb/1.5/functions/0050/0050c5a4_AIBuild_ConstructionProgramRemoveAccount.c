/*
 * Entry: 0050c5a4
 * Name: AIBuild_ConstructionProgramRemoveAccount
 * Namespace: Global
 * Signature: void AIBuild_ConstructionProgramRemoveAccount(tagCONSTRUCTION_PROGRAM * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionProgramRemoveAccount(tagCONSTRUCTION_PROGRAM *param_1,int param_2)

{
  Debug_Assert((int)param_1,0xe2c,".\\Schedule\\Aibuild.cpp","construction_program");
  Debug_Assert((uint)((uint)param_2 < 0x20),0xe2d,".\\Schedule\\Aibuild.cpp",
               "(account_number >=0) && (account_number < AIBUILD_MAX_ACCOUNTS)");
  param_1->account[param_2] = (tagCP_ACCOUNT *)0x0;
  return;
}
