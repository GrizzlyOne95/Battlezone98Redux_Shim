/*
 * Entry: 004af838
 * Name: ScrapDropoff_List
 * Namespace: Global
 * Signature: GameObject * ScrapDropoff_List(int * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl ScrapDropoff_List(int *param_1)

{
  uint uVar1;
  
  if (*param_1 < 0) {
    *param_1 = -1;
  }
  *param_1 = *param_1 + 1;
  uVar1 = *param_1;
  while( true ) {
    if (0x13 < uVar1) {
      return (GameObject *)0x0;
    }
    if (dropoffList[*param_1].dropObj != (ScrapDropoff *)0x0) break;
    *param_1 = *param_1 + 1;
    uVar1 = *param_1;
  }
  return (GameObject *)dropoffList[*param_1].dropObj;
}
