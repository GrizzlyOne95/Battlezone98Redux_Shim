/*
 * Entry: 00549ef3
 * Name: isCyrillic
 * Namespace: Global
 * Signature: int isCyrillic(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isCyrillic(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if ((*param_1 == -0x7c) &&
     (((bVar1 = param_1[1], 0x3f < bVar1 && (bVar1 < 0x61)) || ((0x6f < bVar1 && (bVar1 < 0x92))))))
  {
    return 1;
  }
  return 0;
}
