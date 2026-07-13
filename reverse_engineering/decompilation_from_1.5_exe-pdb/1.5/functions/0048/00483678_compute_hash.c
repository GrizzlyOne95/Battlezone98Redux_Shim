/*
 * Entry: 00483678
 * Name: compute_hash
 * Namespace: Global
 * Signature: int compute_hash(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl compute_hash(char *param_1)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  uVar2 = 0x811c9dc5;
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    uVar1 = tolower((int)*param_1);
    uVar2 = (uVar1 & 0xff ^ uVar2) * 0x1000193;
  }
  return (uVar2 >> 0xb ^ uVar2) & 0x7ff;
}
