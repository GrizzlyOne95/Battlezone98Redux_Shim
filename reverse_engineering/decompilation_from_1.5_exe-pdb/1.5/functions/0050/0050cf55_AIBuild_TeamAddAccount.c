/*
 * Entry: 0050cf55
 * Name: AIBuild_TeamAddAccount
 * Namespace: Global
 * Signature: void AIBuild_TeamAddAccount(tag_team * param_1, int param_2, tagCP_ACCOUNT * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamAddAccount(tag_team *param_1,int param_2,tagCP_ACCOUNT *param_3)

{
  Debug_Assert((int)param_1,0xd8f,".\\Schedule\\Aibuild.cpp","the_team");
  Debug_Assert((int)(param_1->aibuild).construction_program,0xd90,".\\Schedule\\Aibuild.cpp",
               "the_team->aibuild.construction_program");
  Debug_Assert((uint)((uint)param_2 < 0x20),0xd91,".\\Schedule\\Aibuild.cpp",
               "(account_number >=0) && (account_number < AIBUILD_MAX_ACCOUNTS)");
  Debug_Assert((int)param_3,0xd92,".\\Schedule\\Aibuild.cpp","account");
  AIBuild_AccountDelete(((param_1->aibuild).construction_program)->account[param_2]);
  ((param_1->aibuild).construction_program)->account[param_2] = param_3;
  return;
}
