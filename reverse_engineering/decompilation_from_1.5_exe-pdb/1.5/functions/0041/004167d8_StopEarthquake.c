/*
 * Entry: 004167d8
 * Name: StopEarthquake
 * Namespace: Global
 * Signature: void StopEarthquake(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StopEarthquake(void)

{
  EarthQuake::StopQuake(&earthQuake);
  return;
}
