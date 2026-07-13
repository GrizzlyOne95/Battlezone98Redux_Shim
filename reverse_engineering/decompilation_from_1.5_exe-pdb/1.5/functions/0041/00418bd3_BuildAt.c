/*
 * Entry: 00418bd3
 * Name: BuildAt
 * Namespace: Global
 * Signature: int BuildAt(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildAt(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  char *pcVar7;
  
  iVar1 = GetHandle(param_1,1);
  pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
  iVar3 = luaL_optinteger(param_1,4,1);
  pMVar4 = GetMatrix(param_1,3);
  if (pMVar4 == (MAT_3D *)0x0) {
    pVVar5 = GetVector(param_1,3);
    if (pVVar5 == (VECTOR_3D *)0x0) {
      iVar6 = lua_isstring(param_1,3);
      if (iVar6 == 0) {
        iVar6 = GetHandle(param_1,3);
        BuildAt(iVar1,pcVar2,iVar6,iVar3);
      }
      else {
        pcVar7 = lua_tolstring(param_1,3,(uint *)0x0);
        BuildAt(iVar1,pcVar2,pcVar7,iVar3);
      }
    }
    else {
      BuildAt(iVar1,pcVar2,pVVar5,iVar3);
    }
  }
  else {
    BuildAt(iVar1,pcVar2,pMVar4,iVar3);
  }
  return 0;
}
