/*
 * Entry: 0051c1ff
 * Name: Team_SetCredits
 * Namespace: Global
 * Signature: void Team_SetCredits(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_SetCredits(int param_1,int param_2)

{
  Debug_Assert((uint)((uint)param_1 < 0x10),0x45,".\\Schedule\\Team.c",
               "team>=0 && team<TEAM_MAXTEAMS");
  if (param_2 < 0) {
    param_2 = 0;
  }
  teamdata[param_1].credits = param_2;
  return;
}
