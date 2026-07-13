/*
 * Entry: 00417f50
 * Name: ClearScrapAround
 * Namespace: Global
 * Signature: int ClearScrapAround(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ClearScrapAround(lua_State *param_1)

{
  MAT_3D *pMVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  char *pcVar4;
  double dVar5;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  dVar5 = luaL_checknumber(param_1,1);
  local_8 = (float)dVar5;
  pMVar1 = GetMatrix(param_1,2);
  if (pMVar1 == (MAT_3D *)0x0) {
    pVVar2 = GetVector(param_1,2);
    if (pVVar2 == (VECTOR_3D *)0x0) {
      iVar3 = lua_isstring(param_1,2);
      if (iVar3 == 0) {
        iVar3 = GetHandle(param_1,2);
        ClearScrapAround(local_8,iVar3);
        return 0;
      }
      pcVar4 = lua_tolstring(param_1,2,(uint *)0x0);
      iVar3 = luaL_optinteger(param_1,3,0);
      ClearScrapAround(local_8,pcVar4,iVar3);
      return 0;
    }
  }
  else {
    local_20.x = (float)pMVar1->posit_x;
    local_20.y = (float)pMVar1->posit_y;
    local_20.z = (float)pMVar1->posit_z;
    pVVar2 = &local_20;
    local_14 = local_20.x;
    local_10 = local_20.y;
    local_c = local_20.z;
  }
  ClearScrapAround(local_8,pVVar2);
  return 0;
}
