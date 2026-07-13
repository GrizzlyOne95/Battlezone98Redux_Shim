/*
 * Entry: 004188d7
 * Name: Mine
 * Namespace: Global
 * Signature: int Mine(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Mine(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  VECTOR_3D *pVVar3;
  char *pcVar4;
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
      pcVar4 = luaL_checklstring(param_1,2,(uint *)0x0);
      Mine(iVar1,pcVar4,local_8);
    }
    else {
      Mine(iVar1,pVVar3,local_8);
    }
  }
  else {
    local_20.x = (float)pMVar2->posit_x;
    local_20.y = (float)pMVar2->posit_y;
    local_20.z = (float)pMVar2->posit_z;
    local_14 = local_20.x;
    local_10 = local_20.y;
    local_c = local_20.z;
    Mine(iVar1,&local_20,local_8);
  }
  return 0;
}
