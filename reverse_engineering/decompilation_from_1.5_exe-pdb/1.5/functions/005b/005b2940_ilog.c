/*
 * Entry: 005b2940
 * Name: ilog
 * Namespace: Global
 * Signature: int ilog(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ilog(uint param_1)

{
  int iVar1;
  uint in_ECX;
  
  iVar1 = 0;
  for (; in_ECX != 0; in_ECX = in_ECX >> 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}
