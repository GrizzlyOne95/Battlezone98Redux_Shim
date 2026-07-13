/*
 * Entry: 0054a37c
 * Name: jCanEndHere
 * Namespace: Global
 * Signature: int jCanEndHere(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl jCanEndHere(char *param_1,char *param_2)

{
  int iVar1;
  
  if ((param_1 == (char *)0x0) || (param_2 == (char *)0x0)) {
    return -1;
  }
  iVar1 = isOpeningMarks(param_1);
  if ((((iVar1 == 0) && (iVar1 = isClosingMarks(param_2), iVar1 == 0)) &&
      ((iVar1 = isKatakana(param_1), iVar1 == 0 || (iVar1 = isKatakana(param_2), iVar1 == 0)))) &&
     ((((iVar1 = isalnum((int)*param_1), iVar1 == 0 || (iVar1 = isalnum((int)*param_2), iVar1 == 0))
       && ((iVar1 = isRomaji(param_1), iVar1 == 0 || (iVar1 = isRomaji(param_2), iVar1 == 0)))) &&
      (((iVar1 = isGreek(param_1), iVar1 == 0 || (iVar1 = isGreek(param_2), iVar1 == 0)) &&
       ((iVar1 = isCyrillic(param_1), iVar1 == 0 || (iVar1 = isCyrillic(param_2), iVar1 == 0))))))))
  {
    iVar1 = ispunct((int)*param_2);
    return (uint)(iVar1 == 0);
  }
  return 0;
}
