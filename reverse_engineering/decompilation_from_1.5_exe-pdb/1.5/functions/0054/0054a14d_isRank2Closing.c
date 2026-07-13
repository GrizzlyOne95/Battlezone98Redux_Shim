/*
 * Entry: 0054a14d
 * Name: isRank2Closing
 * Namespace: Global
 * Signature: int isRank2Closing(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isRank2Closing(char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  iVar1 = isDipthong(param_1);
  if (iVar1 == 0) {
    iVar1 = isDoubleConsonant(param_1);
    if (iVar1 == 0) {
      iVar1 = isKataParticle(param_1);
      if ((iVar1 == 0) && ((*param_1 != -0x7f || ((param_1[1] != 'X' && (param_1[1] != '[')))))) {
        return 0;
      }
    }
  }
  return 1;
}
