/*
 * Entry: 0054a197
 * Name: isRank3Closing
 * Namespace: Global
 * Signature: int isRank3Closing(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRank3Closing(char *param_1)

{
  byte bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (*param_1 == -0x7f) {
    bVar1 = param_1[1];
    if (bVar1 < 0x5e) {
      if ((0x5b < bVar1) ||
         ((0x49 < bVar1 && ((bVar1 < 0x4c || ((0x51 < bVar1 && (bVar1 < 0x56)))))))) {
        return 1;
      }
    }
    else if (0x8a < bVar1) {
      if (bVar1 < 0x8f) {
        return 1;
      }
      if (bVar1 == 0x93) {
        return 1;
      }
    }
  }
  return 0;
}
