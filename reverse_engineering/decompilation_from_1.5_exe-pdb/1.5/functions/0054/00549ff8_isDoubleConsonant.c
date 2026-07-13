/*
 * Entry: 00549ff8
 * Name: isDoubleConsonant
 * Namespace: Global
 * Signature: int isDoubleConsonant(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isDoubleConsonant(char *param_1)

{
  bool bVar1;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  if (*param_1 == -0x7d) {
    bVar1 = param_1[1] == 'b';
  }
  else {
    if (*param_1 != -0x7e) {
      return 0;
    }
    bVar1 = param_1[1] == -0x3f;
  }
  if (!bVar1) {
    return 0;
  }
  return 1;
}
