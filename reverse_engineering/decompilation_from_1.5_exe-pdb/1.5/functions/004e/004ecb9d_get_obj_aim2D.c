/*
 * Entry: 004ecb9d
 * Name: get_obj_aim2D
 * Namespace: Global
 * Signature: float get_obj_aim2D(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl get_obj_aim2D(_OBJ76 *param_1,_OBJ76 *param_2)

{
  INTER_OBJECT_NODE *pIVar1;
  _OBJ76 *unaff_ESI;
  _OBJ76 *unaff_EDI;
  bool bVar2;
  
  bVar2 = param_2 < param_1;
  if (bVar2) {
    param_1 = param_2;
  }
  pIVar1 = Find_Inter_Object_Info(unaff_EDI,unaff_ESI);
  if (pIVar1 == (INTER_OBJECT_NODE *)0x0) {
    pIVar1 = Add_Inter_Object_Info(param_1,unaff_EDI);
  }
  if (!bVar2) {
    return pIVar1->aimAB;
  }
  return pIVar1->aimBA;
}
