/*
 * Entry: 004e9ff3
 * Name: call_registered_add_funcs
 * Namespace: Global
 * Signature: void call_registered_add_funcs(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl call_registered_add_funcs(tagENTITY *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < AddFunc_Count) {
    do {
      (*AddEntFuncs[iVar1])(param_1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < AddFunc_Count);
  }
  return;
}
