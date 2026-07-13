/*
 * Entry: 0051c2d9
 * Name: Team_Stats_BuildingMade
 * Namespace: Global
 * Signature: void Team_Stats_BuildingMade(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_Stats_BuildingMade(int param_1)

{
  int *piVar1;
  
  piVar1 = &teamdata[param_1].stats.made_buildings;
  *piVar1 = *piVar1 + 1;
  return;
}
