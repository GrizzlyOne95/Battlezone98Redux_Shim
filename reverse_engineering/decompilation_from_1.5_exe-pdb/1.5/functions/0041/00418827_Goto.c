/*
 * Entry: 00418827
 * Name: Goto
 * Namespace: Global
 * Signature: int Goto(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Goto(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  char *pcVar5;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  iVar1 = GetHandle(param_1,1);
  local_8 = luaL_optinteger(param_1,3,1);
  pMVar2 = GetMatrix(param_1,2);
  if (pMVar2 == (MAT_3D *)0x0) {
    pVVar3 = GetVector(param_1,2);
    if (pVVar3 == (VECTOR_3D *)0x0) {
      iVar4 = lua_isstring(param_1,2);
      if (iVar4 != 0) {
        pcVar5 = lua_tolstring(param_1,2,(uint *)0x0);
        Goto(iVar1,pcVar5,local_8);
        return 0;
      }
      iVar4 = GetHandle(param_1,2);
      Goto(iVar1,iVar4,local_8);
      return 0;
    }
  }
  else {
    local_20.x = (float)pMVar2->posit_x;
    local_20.y = (float)pMVar2->posit_y;
    local_20.z = (float)pMVar2->posit_z;
    pVVar3 = &local_20;
    local_14 = local_20.x;
    local_10 = local_20.y;
    local_c = local_20.z;
  }
  Goto(iVar1,pVVar3,local_8);
  return 0;
}
