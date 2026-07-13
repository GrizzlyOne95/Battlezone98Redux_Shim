/*
 * Entry: 0054a2f6
 * Name: isOpeningMarks
 * Namespace: Global
 * Signature: int isOpeningMarks(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isOpeningMarks(char *param_1)

{
  int iVar1;
  char *extraout_EDX;
  char *extraout_EDX_00;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  iVar1 = isRank1Opening(param_1);
  if (iVar1 == 0) {
    iVar1 = isRank2Opening(extraout_EDX);
    if (iVar1 == 0) {
      iVar1 = isHanKataOpening(extraout_EDX_00);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  return 1;
}
