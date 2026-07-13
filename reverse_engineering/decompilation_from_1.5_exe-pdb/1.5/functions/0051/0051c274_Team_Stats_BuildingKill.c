/*
 * Entry: 0051c274
 * Name: Team_Stats_BuildingKill
 * Namespace: Global
 * Signature: void Team_Stats_BuildingKill(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_Stats_BuildingKill(int param_1,int param_2)

{
  int *piVar1;
  
  if (param_1 != param_2) {
    piVar1 = &teamdata[param_1].stats.kills_buildings;
    *piVar1 = *piVar1 + 1;
  }
  piVar1 = &teamdata[param_2].stats.losses_buildings;
  *piVar1 = *piVar1 + 1;
  return;
}
