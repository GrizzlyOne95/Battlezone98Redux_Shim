/*
 * Entry: 00549e7a
 * Name: isKatakana
 * Namespace: Global
 * Signature: int isKatakana(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isKatakana(char *param_1)

{
  int iVar1;
  char *extraout_ECX;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  iVar1 = isHanKata(param_1);
  if (iVar1 == 0) {
    iVar1 = isZenKata(extraout_ECX);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}
