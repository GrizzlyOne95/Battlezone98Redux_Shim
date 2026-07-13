/*
 * Entry: 004166b8
 * Name: Hash
 * Namespace: Global
 * Signature: uint Hash(char * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl Hash(char *param_1,uint param_2)

{
  uint uVar1;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    uVar1 = tolower((int)*param_1);
    param_2 = (uVar1 & 0xff ^ param_2) * 0x1000193;
  }
  return param_2;
}
