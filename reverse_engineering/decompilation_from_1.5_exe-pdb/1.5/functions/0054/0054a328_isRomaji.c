/*
 * Entry: 0054a328
 * Name: isRomaji
 * Namespace: Global
 * Signature: int isRomaji(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRomaji(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 == -0x7e) &&
     ((((bVar1 = param_1[1], 0x4e < bVar1 && (bVar1 < 0x59)) || ((0x5f < bVar1 && (bVar1 < 0x7a))))
      || ((0x80 < bVar1 && (bVar1 < 0x7a)))))) {
    return 1;
  }
  return 0;
}
