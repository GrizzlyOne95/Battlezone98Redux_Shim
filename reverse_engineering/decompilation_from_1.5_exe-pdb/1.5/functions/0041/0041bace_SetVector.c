/*
 * Entry: 0041bace
 * Name: SetVector
 * Namespace: Global
 * Signature: int SetVector(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetVector(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  lua_State *unaff_EDI;
  double dVar2;
  double dVar3;
  double dVar4;
  
  dVar2 = luaL_optnumber(param_1,1,0.0);
  dVar3 = luaL_optnumber(param_1,2,0.0);
  dVar4 = luaL_optnumber(param_1,3,0.0);
  pVVar1 = NewVector(unaff_EDI);
  pVVar1->x = (float)dVar2;
  pVVar1->y = (float)dVar3;
  pVVar1->z = (float)dVar4;
  return 1;
}
