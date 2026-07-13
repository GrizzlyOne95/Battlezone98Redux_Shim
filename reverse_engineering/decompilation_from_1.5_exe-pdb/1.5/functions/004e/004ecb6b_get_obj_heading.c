/*
 * Entry: 004ecb6b
 * Name: get_obj_heading
 * Namespace: Global
 * Signature: float get_obj_heading(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl get_obj_heading(_OBJ76 *param_1)

{
  OBJECT_NODE *pOVar1;
  _OBJ76 *unaff_ESI;
  
  pOVar1 = Find_Object_Info(unaff_ESI);
  if (pOVar1 == (OBJECT_NODE *)0x0) {
    pOVar1 = Add_Object_Info(unaff_ESI);
  }
  return pOVar1->heading;
}
