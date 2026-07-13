/*
 * Entry: 005c7b54
 * Name: _setdefaultprecision
 * Namespace: Global
 * Signature: void _setdefaultprecision(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _setdefaultprecision(void)

{
  int iVar1;
  
  iVar1 = controlfp_s(0,0x10000,0x30000);
  if (iVar1 != 0) {
    invoke_watson(0,0,0,0,0);
    return;
  }
  return;
}
