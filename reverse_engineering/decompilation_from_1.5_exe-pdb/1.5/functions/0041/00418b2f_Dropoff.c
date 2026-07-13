/*
 * Entry: 00418b2f
 * Name: Dropoff
 * Namespace: Global
 * Signature: int Dropoff(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Dropoff(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  MAT_3D *pMVar3;
  VECTOR_3D *pVVar4;
  char *pcVar5;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_optinteger(param_1,3,1);
  pMVar3 = GetMatrix(param_1,2);
  if (pMVar3 == (MAT_3D *)0x0) {
    pVVar4 = GetVector(param_1,2);
    if (pVVar4 == (VECTOR_3D *)0x0) {
      pcVar5 = luaL_checklstring(param_1,2,(uint *)0x0);
      Dropoff(iVar1,pcVar5,iVar2);
    }
    else {
      Dropoff(iVar1,pVVar4,iVar2);
    }
  }
  else {
    Dropoff(iVar1,pMVar3,iVar2);
  }
  return 0;
}
