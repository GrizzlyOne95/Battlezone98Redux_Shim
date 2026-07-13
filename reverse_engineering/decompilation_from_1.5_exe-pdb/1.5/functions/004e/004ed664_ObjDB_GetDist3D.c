/*
 * Entry: 004ed664
 * Name: ObjDB_GetDist3D
 * Namespace: Global
 * Signature: float ObjDB_GetDist3D(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ObjDB_GetDist3D(_OBJ76 *param_1,_OBJ76 *param_2)

{
  INTER_OBJECT_NODE *pIVar1;
  _OBJ76 *unaff_ESI;
  _OBJ76 *unaff_EDI;
  
  if (param_2 < param_1) {
    param_1 = param_2;
  }
  pIVar1 = Find_Inter_Object_Info(unaff_EDI,unaff_ESI);
  if (pIVar1 == (INTER_OBJECT_NODE *)0x0) {
    pIVar1 = Add_Inter_Object_Info(param_1,unaff_EDI);
  }
  return pIVar1->dist_3D;
}
