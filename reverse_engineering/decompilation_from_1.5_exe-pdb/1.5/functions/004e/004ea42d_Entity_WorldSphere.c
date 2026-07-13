/*
 * Entry: 004ea42d
 * Name: Entity_WorldSphere
 * Namespace: Global
 * Signature: SPHERE * Entity_WorldSphere(SPHERE * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SPHERE * __cdecl Entity_WorldSphere(SPHERE *__return_storage_ptr__,tagENTITY *param_1)

{
  __return_storage_ptr__->radius = (param_1->bSphere).radius;
  Vector_Transform(&__return_storage_ptr__->origin,&(param_1->bSphere).origin,1,
                   &param_1->obj76->transform);
  return __return_storage_ptr__;
}
