/*
 * Entry: 0041bd76
 * Name: SetMatrix
 * Namespace: Global
 * Signature: int SetMatrix(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetMatrix(lua_State *param_1)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  MAT_3D *pMVar5;
  double dVar6;
  lua_State *plVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  
  dVar6 = luaL_optnumber(param_1,1,0.0);
  plVar7 = (lua_State *)(float)dVar6;
  dVar6 = luaL_optnumber(param_1,2,0.0);
  fVar8 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,3,0.0);
  fVar9 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,4,0.0);
  fVar10 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,5,0.0);
  fVar11 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,6,0.0);
  fVar12 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,7,0.0);
  fVar13 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,8,0.0);
  fVar14 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,9,0.0);
  fVar15 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,10,0.0);
  fVar16 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,0xb,0.0);
  fVar17 = (float)dVar6;
  dVar6 = luaL_optnumber(param_1,0xc,0.0);
  fVar18 = (float)dVar6;
  pMVar5 = NewMatrix(plVar7);
  VVar1.y = fVar8;
  VVar1.x = (float)plVar7;
  VVar1.z = fVar9;
  VVar2.y = fVar11;
  VVar2.x = fVar10;
  VVar2.z = fVar12;
  VVar3.y = fVar14;
  VVar3.x = fVar13;
  VVar3.z = fVar15;
  VVar4.y = fVar17;
  VVar4.x = fVar16;
  VVar4.z = fVar18;
  Matrix_Set(pMVar5,VVar1,VVar2,VVar3,VVar4);
  return 1;
}
