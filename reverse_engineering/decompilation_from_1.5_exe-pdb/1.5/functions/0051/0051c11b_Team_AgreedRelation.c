/*
 * Entry: 0051c11b
 * Name: Team_AgreedRelation
 * Namespace: Global
 * Signature: uchar Team_AgreedRelation(int param_1, int param_2, TEAM_RELATION param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl Team_AgreedRelation(int param_1,int param_2,TEAM_RELATION param_3)

{
  uchar uVar1;
  
  Debug_Assert((uint)((uint)param_1 < 0x10),0x22,".\\Schedule\\Team.c",
               "team1>=0 && team1<TEAM_MAXTEAMS");
  Debug_Assert((uint)((uint)param_2 < 0x10),0x23,".\\Schedule\\Team.c",
               "team2>=0 && team2<TEAM_MAXTEAMS");
  if ((teamdata[param_1].relation[param_2] == param_3) &&
     (teamdata[param_2].relation[param_1] == param_3)) {
    uVar1 = '\x01';
  }
  else {
    uVar1 = '\0';
  }
  return uVar1;
}
