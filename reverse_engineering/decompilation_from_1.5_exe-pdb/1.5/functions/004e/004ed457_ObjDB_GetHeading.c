/*
 * Entry: 004ed457
 * Name: ObjDB_GetHeading
 * Namespace: Global
 * Signature: float ObjDB_GetHeading(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ObjDB_GetHeading(_OBJ76 *param_1)

{
  OBJECT_NODE *pOVar1;
  _OBJ76 *unaff_ESI;
  
  pOVar1 = Find_Object_Info(unaff_ESI);
  if (pOVar1 == (OBJECT_NODE *)0x0) {
    pOVar1 = Add_Object_Info(unaff_ESI);
  }
  return pOVar1->heading;
}
