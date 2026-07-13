/*
 * Entry: 0050830f
 * Name: AI_EnableTeam
 * Namespace: Global
 * Signature: int AI_EnableTeam(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_EnableTeam(int param_1)

{
  int iVar1;
  
  Debug_Assert((uint)((uint)param_1 < 0x10),0x185,".\\Schedule\\Ai.cpp",
               "(team >= 0) && (team < TEAM_MAXTEAMS)");
  iVar1 = AI_IsAITeam(param_1);
  if ((iVar1 != 0) && (ai_team_enabled[param_1] == 0)) {
    ai_team_enabled[param_1] = 1;
    return 1;
  }
  return 0;
}
