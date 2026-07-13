/*
 * Entry: 00419b87
 * Name: GetTerrainHeightAndNormal
 * Namespace: Global
 * Signature: int GetTerrainHeightAndNormal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTerrainHeightAndNormal(lua_State *param_1)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  char *pcVar5;
  lua_State *unaff_EDI;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float local_c;
  float local_8;
  
  GetMatrix(param_1,1);
  pVVar3 = GetVector(param_1,1);
  if (pVVar3 == (VECTOR_3D *)0x0) {
    iVar4 = lua_isstring(param_1,3);
    if (iVar4 == 0) {
      iVar4 = GetHandle(param_1,3);
      pVVar3 = GetPosition(&local_2c,iVar4);
    }
    else {
      pcVar5 = lua_tolstring(param_1,3,(uint *)0x0);
      iVar4 = luaL_optinteger(param_1,4,0);
      pVVar3 = GetPosition(&local_2c,pcVar5,iVar4);
    }
    fVar1 = pVVar3->x;
    fStack_10 = pVVar3->y;
    fVar2 = pVVar3->z;
    local_14 = fVar1;
    local_c = fVar2;
  }
  else {
    fVar1 = pVVar3->x;
    fVar2 = pVVar3->z;
  }
  Terrain_GetHeightAndNormal((double)fVar1,(double)fVar2,&local_8,&local_20);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)local_8 >> 0x20)));
  pVVar3 = NewVector(unaff_EDI);
  pVVar3->x = local_20.x;
  pVVar3->y = local_20.y;
  pVVar3->z = local_20.z;
  return 2;
}
