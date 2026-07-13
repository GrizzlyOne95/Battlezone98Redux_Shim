/*
 * Entry: 004167b2
 * Name: StartEarthquake
 * Namespace: Global
 * Signature: void StartEarthquake(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StartEarthquake(float param_1)

{
  EarthQuake::StartQuake(&earthQuake,param_1);
  return;
}
