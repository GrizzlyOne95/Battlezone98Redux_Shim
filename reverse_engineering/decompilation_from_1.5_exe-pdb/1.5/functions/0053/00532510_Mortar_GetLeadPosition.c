/*
 * Entry: 00532510
 * Name: Mortar::GetLeadPosition
 * Namespace: Mortar
 * Signature: VECTOR_3D * GetLeadPosition(Mortar * this, VECTOR_3D * __return_storage_ptr__, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall
Mortar::GetLeadPosition(Mortar *this,VECTOR_3D *__return_storage_ptr__,GameObject *param_1)

{
  GetLeadPosition(this,__return_storage_ptr__,(float *)&param_1,param_1,true);
  return __return_storage_ptr__;
}
