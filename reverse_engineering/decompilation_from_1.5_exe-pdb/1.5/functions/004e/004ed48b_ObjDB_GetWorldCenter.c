/*
 * Entry: 004ed48b
 * Name: ObjDB_GetWorldCenter
 * Namespace: Global
 * Signature: VECTOR_3D * ObjDB_GetWorldCenter(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl ObjDB_GetWorldCenter(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1)

{
  OBJECT_NODE *pOVar1;
  _OBJ76 *unaff_EDI;
  
  pOVar1 = Find_Object_Info(unaff_EDI);
  if (pOVar1 == (OBJECT_NODE *)0x0) {
    pOVar1 = Add_Object_Info(unaff_EDI);
  }
  __return_storage_ptr__->x = (pOVar1->sphere).origin.x;
  __return_storage_ptr__->y = (pOVar1->sphere).origin.y;
  __return_storage_ptr__->z = (pOVar1->sphere).origin.z;
  return __return_storage_ptr__;
}
