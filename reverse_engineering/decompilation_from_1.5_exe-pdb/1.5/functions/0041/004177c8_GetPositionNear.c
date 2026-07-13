/*
 * Entry: 004177c8
 * Name: GetPositionNear
 * Namespace: Global
 * Signature: int GetPositionNear(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPositionNear(lua_State *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D *pVVar2;
  lua_State *unaff_EDI;
  double dVar3;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  float local_8;
  
  pVVar1 = GetVector(param_1,1);
  if (pVVar1 != (VECTOR_3D *)0x0) {
    dVar3 = luaL_optnumber(param_1,2,0.0);
    local_8 = (float)dVar3;
    dVar3 = luaL_optnumber(param_1,3,0.0);
    pVVar2 = GetPositionNear(&local_20,pVVar1,local_8,(float)dVar3);
    local_14 = pVVar2->x;
    fStack_10 = pVVar2->y;
    fStack_c = pVVar2->z;
    pVVar2 = NewVector(unaff_EDI);
    pVVar2->x = local_14;
    pVVar2->y = fStack_10;
    pVVar2->z = fStack_c;
  }
  return (uint)(pVVar1 != (VECTOR_3D *)0x0);
}
