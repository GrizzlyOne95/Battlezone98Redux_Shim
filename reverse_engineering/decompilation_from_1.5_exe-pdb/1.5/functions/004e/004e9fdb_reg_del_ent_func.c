/*
 * Entry: 004e9fdb
 * Name: reg_del_ent_func
 * Namespace: Global
 * Signature: void reg_del_ent_func(_func___cdecl_void_tagENTITY_ptr * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl reg_del_ent_func(_func___cdecl_void_tagENTITY_ptr *param_1)

{
  long lVar1;
  
  lVar1 = DelFunc_Count;
  DelFunc_Count = DelFunc_Count + 1;
  DelEntFuncs[lVar1] = param_1;
  return;
}
