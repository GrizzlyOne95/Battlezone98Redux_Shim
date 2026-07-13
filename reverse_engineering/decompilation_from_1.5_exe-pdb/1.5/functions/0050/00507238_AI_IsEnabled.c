/*
 * Entry: 00507238
 * Name: AI_IsEnabled
 * Namespace: Global
 * Signature: int AI_IsEnabled(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_IsEnabled(int param_1)

{
  int iVar1;
  
  Debug_Assert((uint)((uint)param_1 < 0x10),0x1ac,".\\Schedule\\Ai.cpp",
               "(team >= 0) && (team < TEAM_MAXTEAMS)");
  iVar1 = AI_IsAITeam(param_1);
  if ((iVar1 == 0) || (iVar1 = 1, ai_team_enabled[param_1] != 1)) {
    iVar1 = 0;
  }
  return iVar1;
}
