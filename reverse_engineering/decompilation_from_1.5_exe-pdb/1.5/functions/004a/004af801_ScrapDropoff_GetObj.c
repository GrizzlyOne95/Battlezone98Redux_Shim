/*
 * Entry: 004af801
 * Name: ScrapDropoff_GetObj
 * Namespace: Global
 * Signature: GameObject * ScrapDropoff_GetObj(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl ScrapDropoff_GetObj(int param_1)

{
  if (param_1 < 0) {
    return (GameObject *)0x0;
  }
  return (GameObject *)dropoffList[param_1].dropObj;
}
