/*
 * Entry: 0051c2c6
 * Name: Team_Stats_UnitMade
 * Namespace: Global
 * Signature: void Team_Stats_UnitMade(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team_Stats_UnitMade(int param_1)

{
  int *piVar1;
  
  piVar1 = &teamdata[param_1].stats.made_units;
  *piVar1 = *piVar1 + 1;
  return;
}
