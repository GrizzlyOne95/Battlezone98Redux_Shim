/*
 * Entry: 0041bee5
 * Name: SetPosition
 * Namespace: Global
 * Signature: int SetPosition(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetPosition(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  char *pcVar5;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = GetHandle(param_1,1);
  pMVar2 = GetMatrix(param_1,2);
  if (pMVar2 == (MAT_3D *)0x0) {
    pVVar3 = GetVector(param_1,2);
    if (pVVar3 == (VECTOR_3D *)0x0) {
      iVar4 = lua_isstring(param_1,2);
      if (iVar4 == 0) {
        return 0;
      }
      pcVar5 = luaL_checklstring(param_1,2,(uint *)0x0);
      iVar4 = luaL_optinteger(param_1,3,0);
      SetPosition(iVar1,pcVar5,iVar4);
      return 0;
    }
  }
  else {
    local_1c.x = (float)pMVar2->posit_x;
    local_1c.y = (float)pMVar2->posit_y;
    local_1c.z = (float)pMVar2->posit_z;
    pVVar3 = &local_1c;
    local_10 = local_1c.x;
    local_c = local_1c.y;
    local_8 = local_1c.z;
  }
  SetPosition(iVar1,pVVar3);
  return 0;
}
