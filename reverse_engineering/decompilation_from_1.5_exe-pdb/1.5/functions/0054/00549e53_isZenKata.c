/*
 * Entry: 00549e53
 * Name: isZenKata
 * Namespace: Global
 * Signature: int isZenKata(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isZenKata(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((((*param_1 == -0x7d) && (bVar1 = param_1[1], 0x3f < bVar1)) && (bVar1 < 0x97)) &&
     (bVar1 != 0x7f)) {
    return 1;
  }
  return 0;
}
