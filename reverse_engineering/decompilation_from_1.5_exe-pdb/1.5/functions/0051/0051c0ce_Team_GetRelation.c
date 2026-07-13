/*
 * Entry: 0051c0ce
 * Name: Team_GetRelation
 * Namespace: Global
 * Signature: TEAM_RELATION Team_GetRelation(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEAM_RELATION __cdecl Team_GetRelation(int param_1,int param_2)

{
  Debug_Assert((uint)((uint)param_1 < 0x10),0x18,".\\Schedule\\Team.c",
               "team1>=0 && team1<TEAM_MAXTEAMS");
  Debug_Assert((uint)((uint)param_2 < 0x10),0x19,".\\Schedule\\Team.c",
               "team2>=0 && team2<TEAM_MAXTEAMS");
  return teamdata[param_1].relation[param_2];
}
