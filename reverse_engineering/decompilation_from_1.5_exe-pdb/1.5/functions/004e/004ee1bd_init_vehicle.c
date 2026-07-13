/*
 * Entry: 004ee1bd
 * Name: init_vehicle
 * Namespace: Global
 * Signature: void init_vehicle(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl init_vehicle(_OBJ76 *param_1)

{
  void *pvVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  pvVar1 = param_1->class_ptr;
  p_Var2 = obj_find_class(param_1,CLASS_ID_EYEPOINT);
  *(_OBJ76 **)((int)pvVar1 + 0xf4) = p_Var2;
  iVar3 = is_user_vhcl(param_1);
  if (iVar3 != 0) {
    Init_View_Record(1);
  }
  return;
}
