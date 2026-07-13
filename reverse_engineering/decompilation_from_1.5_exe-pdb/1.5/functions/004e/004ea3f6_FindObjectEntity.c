/*
 * Entry: 004ea3f6
 * Name: FindObjectEntity
 * Namespace: Global
 * Signature: tagENTITY * FindObjectEntity(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl FindObjectEntity(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  int iVar2;
  tagENTITY *ptVar3;
  
  p_Var1 = obj_get_root(param_1);
  iVar2 = 0;
  ptVar3 = world;
  do {
    if (ptVar3->obj76 == p_Var1) {
      return world + iVar2;
    }
    ptVar3 = ptVar3 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)ptVar3 < 0xbd7390);
  return (tagENTITY *)0x0;
}
