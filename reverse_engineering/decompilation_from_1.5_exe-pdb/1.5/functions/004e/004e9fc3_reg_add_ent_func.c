/*
 * Entry: 004e9fc3
 * Name: reg_add_ent_func
 * Namespace: Global
 * Signature: void reg_add_ent_func(_func___cdecl_void_tagENTITY_ptr * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl reg_add_ent_func(_func___cdecl_void_tagENTITY_ptr *param_1)

{
  long lVar1;
  
  lVar1 = AddFunc_Count;
  AddFunc_Count = AddFunc_Count + 1;
  AddEntFuncs[lVar1] = param_1;
  return;
}
