/*
 * Entry: 0050c44b
 * Name: AIBuild_TeamRemoveAccount
 * Namespace: Global
 * Signature: void AIBuild_TeamRemoveAccount(tag_team * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_TeamRemoveAccount(tag_team *param_1,int param_2)

{
  Debug_Assert((int)param_1,0xdab,".\\Schedule\\Aibuild.cpp","the_team");
  Debug_Assert((int)(param_1->aibuild).construction_program,0xdac,".\\Schedule\\Aibuild.cpp",
               "the_team->aibuild.construction_program");
  Debug_Assert((uint)((uint)param_2 < 0x20),0xdad,".\\Schedule\\Aibuild.cpp",
               "(account_number >=0) && (account_number < AIBUILD_MAX_ACCOUNTS)");
  ((param_1->aibuild).construction_program)->account[param_2] = (tagCP_ACCOUNT *)0x0;
  return;
}
