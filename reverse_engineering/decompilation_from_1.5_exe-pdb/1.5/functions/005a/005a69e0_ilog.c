/*
 * Entry: 005a69e0
 * Name: _ilog
 * Namespace: Global
 * Signature: int _ilog(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ilog(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 >> 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}
