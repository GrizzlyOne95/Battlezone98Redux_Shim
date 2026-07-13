/*
 * Entry: 0054a218
 * Name: isClosingMarks
 * Namespace: Global
 * Signature: int isClosingMarks(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isClosingMarks(char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  iVar1 = isRank1Closing(param_1);
  if (iVar1 == 0) {
    iVar1 = isRank2Closing(param_1);
    if (iVar1 == 0) {
      iVar1 = isRank3Closing(param_1);
      if (iVar1 == 0) {
        iVar1 = isHanKataClosing(param_1);
        if (iVar1 == 0) {
          return 0;
        }
      }
    }
  }
  return 1;
}
