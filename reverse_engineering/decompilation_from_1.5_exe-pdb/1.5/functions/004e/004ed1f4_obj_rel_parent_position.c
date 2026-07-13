/*
 * Entry: 004ed1f4
 * Name: obj_rel_parent_position
 * Namespace: Global
 * Signature: VECTOR_3D * obj_rel_parent_position(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
obj_rel_parent_position(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1,_OBJ76 *param_2)

{
  double dVar1;
  double dVar2;
  _OBJ76 *p_Var3;
  
  dVar1 = (param_1->transform).posit_y;
  dVar2 = (param_1->transform).posit_z;
  __return_storage_ptr__->x = (float)(param_1->transform).posit_x;
  __return_storage_ptr__->y = (float)dVar1;
  __return_storage_ptr__->z = (float)dVar2;
  for (p_Var3 = param_1->parent; (p_Var3 != (_OBJ76 *)0x0 && (p_Var3 != param_2));
      p_Var3 = p_Var3->parent) {
    Vector_Transform(__return_storage_ptr__,__return_storage_ptr__,1,&p_Var3->transform);
  }
  return __return_storage_ptr__;
}
