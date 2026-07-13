/*
 * Entry: 0051c29d
 * Name: Team_Stats_UnitKill
 * Namespace: Global
 * Signature: void Team_Stats_UnitKill(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_Stats_UnitKill(int param_1,int param_2)

{
  int *piVar1;
  
  if (param_1 != param_2) {
    teamdata[param_1].stats.kills_units = teamdata[param_1].stats.kills_units + 1;
  }
  piVar1 = &teamdata[param_2].stats.losses_units;
  *piVar1 = *piVar1 + 1;
  return;
}
