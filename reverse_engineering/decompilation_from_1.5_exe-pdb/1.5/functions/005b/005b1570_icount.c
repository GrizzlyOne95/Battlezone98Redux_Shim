/*
 * Entry: 005b1570
 * Name: icount
 * Namespace: Global
 * Signature: int icount(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl icount(uint param_1)

{
  int iVar1;
  uint in_ECX;
  
  iVar1 = 0;
  for (; in_ECX != 0; in_ECX = in_ECX >> 1) {
    iVar1 = iVar1 + (in_ECX & 1);
  }
  return iVar1;
}
