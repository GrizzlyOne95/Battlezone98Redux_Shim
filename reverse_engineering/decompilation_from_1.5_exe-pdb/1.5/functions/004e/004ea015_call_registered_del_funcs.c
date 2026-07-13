/*
 * Entry: 004ea015
 * Name: call_registered_del_funcs
 * Namespace: Global
 * Signature: void call_registered_del_funcs(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl call_registered_del_funcs(tagENTITY *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < DelFunc_Count) {
    do {
      (*DelEntFuncs[iVar1])(param_1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < DelFunc_Count);
  }
  return;
}
