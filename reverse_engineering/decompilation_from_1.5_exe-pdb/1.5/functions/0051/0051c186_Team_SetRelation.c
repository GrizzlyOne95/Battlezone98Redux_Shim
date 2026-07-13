/*
 * Entry: 0051c186
 * Name: Team_SetRelation
 * Namespace: Global
 * Signature: void Team_SetRelation(int param_1, int param_2, TEAM_RELATION param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_SetRelation(int param_1,int param_2,TEAM_RELATION param_3)

{
  Debug_Assert((uint)((uint)param_1 < 0x10),0x2d,".\\Schedule\\Team.c",
               "team1>=0 && team1<TEAM_MAXTEAMS");
  Debug_Assert((uint)((uint)param_2 < 0x10),0x2e,".\\Schedule\\Team.c",
               "team2>=0 && team2<TEAM_MAXTEAMS");
  if (param_1 == param_2) {
    param_3 = TR_ALLY;
  }
  teamdata[param_1].relation[param_2] = param_3;
  Units_UpdateRelationRelatedInformationForTeam(param_1);
  Units_UpdateRelationRelatedInformationForTeam(param_2);
  Build_ScanFogForTeam(param_1);
  Build_ScanFogForTeam(param_2);
  return;
}
