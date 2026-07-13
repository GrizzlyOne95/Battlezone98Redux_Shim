/*
 * Entry: 004ecaf7
 * Name: find_textured_obj_in_subtree
 * Namespace: Global
 * Signature: _OBJ76 * find_textured_obj_in_subtree(_OBJ76 * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl find_textured_obj_in_subtree(_OBJ76 *param_1,char *param_2)

{
  FACE *pFVar1;
  int iVar2;
  _OBJ76 *p_Var3;
  _OBJ76 *p_Var4;
  
  p_Var4 = (_OBJ76 *)0x0;
  GeoCache_SelectLOD(param_1,4);
  if ((((param_1->geom == (_GEOMETRY *)0x0) ||
       (pFVar1 = param_1->geom->faces, pFVar1 == (FACE *)0x0)) ||
      (iVar2 = _strnicmp(pFVar1->texture_name,param_2,0x10), p_Var3 = param_1, iVar2 != 0)) &&
     (((param_1->child == (_OBJ76 *)0x0 ||
       (p_Var4 = find_textured_obj_in_subtree(param_1->child,param_2), p_Var3 = p_Var4,
       p_Var4 == (_OBJ76 *)0x0)) && (p_Var3 = p_Var4, param_1->sibling != (_OBJ76 *)0x0)))) {
    p_Var3 = find_textured_obj_in_subtree(param_1->sibling,param_2);
  }
  return p_Var3;
}
