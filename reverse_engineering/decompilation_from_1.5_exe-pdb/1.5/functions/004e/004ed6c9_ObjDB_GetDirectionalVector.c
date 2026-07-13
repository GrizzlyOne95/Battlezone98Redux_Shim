/*
 * Entry: 004ed6c9
 * Name: ObjDB_GetDirectionalVector
 * Namespace: Global
 * Signature: VECTOR_3D * ObjDB_GetDirectionalVector(VECTOR_3D * __return_storage_ptr__, _OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
ObjDB_GetDirectionalVector(VECTOR_3D *__return_storage_ptr__,_OBJ76 *param_1,_OBJ76 *param_2)

{
  INTER_OBJECT_NODE *pIVar1;
  _OBJ76 *unaff_ESI;
  VECTOR_3D *pVVar2;
  _OBJ76 *unaff_EDI;
  bool bVar3;
  
  bVar3 = param_2 < param_1;
  if (bVar3) {
    param_1 = param_2;
  }
  pIVar1 = Find_Inter_Object_Info(unaff_EDI,unaff_ESI);
  if (pIVar1 == (INTER_OBJECT_NODE *)0x0) {
    pIVar1 = Add_Inter_Object_Info(param_1,unaff_EDI);
  }
  pVVar2 = &pIVar1->dirvecAB;
  if (bVar3) {
    pVVar2 = &pIVar1->dirvecBA;
  }
  __return_storage_ptr__->x = pVVar2->x;
  __return_storage_ptr__->y = pVVar2->y;
  __return_storage_ptr__->z = pVVar2->z;
  return __return_storage_ptr__;
}
