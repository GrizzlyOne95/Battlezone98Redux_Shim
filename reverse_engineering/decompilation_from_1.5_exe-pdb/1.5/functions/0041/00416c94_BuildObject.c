/*
 * Entry: 00416c94
 * Name: BuildObject
 * Namespace: Global
 * Signature: int BuildObject(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildObject(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  MAT_3D *pMVar3;
  VECTOR_3D *pVVar4;
  int iVar5;
  char *pcVar6;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar2 = luaL_checkinteger(param_1,2);
  pMVar3 = GetMatrix(param_1,3);
  if (pMVar3 == (MAT_3D *)0x0) {
    pVVar4 = GetVector(param_1,3);
    if (pVVar4 == (VECTOR_3D *)0x0) {
      iVar5 = lua_isstring(param_1,3);
      if (iVar5 == 0) {
        iVar5 = GetHandle(param_1,3);
        iVar2 = BuildObject(pcVar1,iVar2,iVar5);
      }
      else {
        pcVar6 = lua_tolstring(param_1,3,(uint *)0x0);
        iVar5 = luaL_optinteger(param_1,4,0);
        iVar2 = BuildObject(pcVar1,iVar2,pcVar6,iVar5);
      }
    }
    else {
      iVar2 = BuildObject(pcVar1,iVar2,pVVar4);
    }
  }
  else {
    iVar2 = BuildObject(pcVar1,iVar2,pMVar3);
  }
  PushHandle(param_1,iVar2);
  return 1;
}
