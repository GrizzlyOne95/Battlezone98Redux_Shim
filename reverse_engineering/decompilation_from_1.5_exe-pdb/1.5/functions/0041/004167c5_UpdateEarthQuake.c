/*
 * Entry: 004167c5
 * Name: UpdateEarthQuake
 * Namespace: Global
 * Signature: void UpdateEarthQuake(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateEarthQuake(float param_1)

{
  EarthQuake::UpdateQuake(&earthQuake,param_1);
  return;
}
