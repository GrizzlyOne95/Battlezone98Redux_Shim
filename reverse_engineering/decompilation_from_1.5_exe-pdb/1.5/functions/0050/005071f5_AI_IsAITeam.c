/*
 * Entry: 005071f5
 * Name: AI_IsAITeam
 * Namespace: Global
 * Signature: int AI_IsAITeam(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_IsAITeam(int param_1)

{
  Debug_Assert((uint)((uint)param_1 < 0x10),0x1a0,".\\Schedule\\Ai.cpp",
               "(team >= 0) && (team < TEAM_MAXTEAMS)");
  if (AI_map->team[param_1] == (tag_team *)0x0) {
    return 0;
  }
  return (uint)teamdata[param_1].aicontrol;
}
