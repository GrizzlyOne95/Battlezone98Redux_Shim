/*
 * Entry: 0051ec4b
 * Name: FreeTerrainSpecials
 * Namespace: Global
 * Signature: void FreeTerrainSpecials(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeTerrainSpecials(void)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  
  p_Var2 = TerrainSpecialList;
  while (p_Var2 != (_OBJ76 *)0x0) {
    p_Var1 = p_Var2->sibling;
    remove_obj(p_Var2,".\\Terrain\\Terramap.c");
    p_Var2 = p_Var1;
  }
  TerrainSpecialList = (_OBJ76 *)0x0;
  return;
}
