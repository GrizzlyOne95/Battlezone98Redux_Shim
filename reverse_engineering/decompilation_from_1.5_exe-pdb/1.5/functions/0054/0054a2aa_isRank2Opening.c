/*
 * Entry: 0054a2aa
 * Name: isRank2Opening
 * Namespace: Global
 * Signature: int isRank2Opening(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRank2Opening(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (((*param_1 == -0x7f) && (bVar1 = param_1[1], 0x8e < bVar1)) &&
     (((bVar1 < 0x93 || (bVar1 == 0x94)) || ((0x96 < bVar1 && ((bVar1 < 0x99 || (bVar1 == 0xa7))))))
     )) {
    return 1;
  }
  return 0;
}
