/*
 * Entry: 0054a1e8
 * Name: isHanKataClosing
 * Namespace: Global
 * Signature: int isHanKataClosing(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isHanKataClosing(char *param_1)

{
  char cVar1;
  int iVar2;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  cVar1 = *param_1;
  if ((((cVar1 != -0x5c) && (cVar1 != -0x5f)) && (cVar1 != -0x5b)) && (cVar1 != -0x5d)) {
    iVar2 = isVoicingMark(param_1);
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}
