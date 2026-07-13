/*
 * Entry: 0051c239
 * Name: Team_ChangeCredits
 * Namespace: Global
 * Signature: void Team_ChangeCredits(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_ChangeCredits(int param_1,int param_2)

{
  int *piVar1;
  
  Debug_Assert((uint)((uint)param_1 < 0x10),0x4d,".\\Schedule\\Team.c",
               "team>=0 && team<TEAM_MAXTEAMS");
  piVar1 = &teamdata[param_1].credits;
  *piVar1 = *piVar1 + param_2;
  if (*piVar1 < 0) {
    *piVar1 = 0;
  }
  return;
}
