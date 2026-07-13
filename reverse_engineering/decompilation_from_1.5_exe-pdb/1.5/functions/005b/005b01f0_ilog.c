/*
 * Entry: 005b01f0
 * Name: ilog
 * Namespace: Global
 * Signature: int ilog(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ilog(uint param_1)

{
  int iVar1;
  int in_ECX;
  uint uVar2;
  
  iVar1 = 0;
  if (in_ECX != 0) {
    for (uVar2 = in_ECX - 1; uVar2 != 0; uVar2 = uVar2 >> 1) {
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}
