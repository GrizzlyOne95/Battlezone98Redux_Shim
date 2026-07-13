/*
 * Entry: 00549fcb
 * Name: isFinalN
 * Namespace: Global
 * Signature: int isFinalN(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isFinalN(char *param_1)

{
  char cVar1;
  bool bVar2;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  cVar1 = *param_1;
  if (cVar1 != -0x23) {
    if (cVar1 == -0x7d) {
      bVar2 = param_1[1] == -0x6d;
    }
    else {
      if (cVar1 != -0x7e) {
        return 0;
      }
      bVar2 = param_1[1] == -0xf;
    }
    if (!bVar2) {
      return 0;
    }
  }
  return 1;
}
