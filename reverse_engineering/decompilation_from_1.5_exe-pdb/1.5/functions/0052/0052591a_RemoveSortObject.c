/*
 * Entry: 0052591a
 * Name: RemoveSortObject
 * Namespace: Global
 * Signature: void RemoveSortObject(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RemoveSortObject(tagENTITY *param_1)

{
  _GEOMETRY *p_Var1;
  
  if (((param_1 != (tagENTITY *)0x0) && (param_1->obj76 != (_OBJ76 *)0x0)) &&
     (p_Var1 = param_1->obj76->geom, p_Var1 != (_GEOMETRY *)0x0)) {
    Geom_Delete(p_Var1);
    param_1->obj76->geom = (_GEOMETRY *)0x0;
  }
  return;
}
