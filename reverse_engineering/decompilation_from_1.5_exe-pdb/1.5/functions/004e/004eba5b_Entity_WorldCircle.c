/*
 * Entry: 004eba5b
 * Name: Entity_WorldCircle
 * Namespace: Global
 * Signature: CIRCLE * Entity_WorldCircle(CIRCLE * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CIRCLE * __cdecl Entity_WorldCircle(CIRCLE *__return_storage_ptr__,tagENTITY *param_1)

{
  _OBJ76 *p_Var1;
  VECTOR_3D local_18;
  
  p_Var1 = param_1->obj76;
  __return_storage_ptr__->radius = (param_1->bSphere).radius;
  Vector_Transform(&local_18,&(param_1->bSphere).origin,1,&p_Var1->transform);
  (__return_storage_ptr__->origin).x = local_18.x;
  (__return_storage_ptr__->origin).z = local_18.z;
  return __return_storage_ptr__;
}
