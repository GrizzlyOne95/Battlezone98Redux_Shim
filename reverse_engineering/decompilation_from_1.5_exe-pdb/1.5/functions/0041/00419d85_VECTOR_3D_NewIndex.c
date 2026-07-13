/*
 * Entry: 00419d85
 * Name: VECTOR_3D_NewIndex
 * Namespace: Global
 * Signature: int VECTOR_3D_NewIndex(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VECTOR_3D_NewIndex(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  char *pcVar2;
  uint uVar3;
  double dVar4;
  
  pVVar1 = GetVector(param_1,1);
  if (pVVar1 != (VECTOR_3D *)0x0) {
    pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
    uVar3 = Hash(pcVar2,0x811c9dc5);
    if (uVar3 == 0xfc0c4ef4) {
      dVar4 = luaL_checknumber(param_1,3);
      pVVar1->y = (float)dVar4;
    }
    else if (uVar3 == 0xfd0c5087) {
      dVar4 = luaL_checknumber(param_1,3);
      pVVar1->x = (float)dVar4;
    }
    else if (uVar3 == 0xff0c53ad) {
      dVar4 = luaL_checknumber(param_1,3);
      pVVar1->z = (float)dVar4;
    }
  }
  return 0;
}
