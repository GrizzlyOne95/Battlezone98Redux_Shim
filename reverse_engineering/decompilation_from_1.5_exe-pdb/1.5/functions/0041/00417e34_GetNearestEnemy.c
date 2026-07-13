/*
 * Entry: 00417e34
 * Name: GetNearestEnemy
 * Namespace: Global
 * Signature: int GetNearestEnemy(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNearestEnemy(lua_State *param_1)

{
  MAT_3D *pMVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  char *pcVar4;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  pMVar1 = GetMatrix(param_1,1);
  if (pMVar1 == (MAT_3D *)0x0) {
    pVVar2 = GetVector(param_1,1);
    if (pVVar2 == (VECTOR_3D *)0x0) {
      iVar3 = lua_isstring(param_1,1);
      if (iVar3 == 0) {
        iVar3 = GetHandle(param_1,1);
        iVar3 = GetNearestEnemy(iVar3);
      }
      else {
        pcVar4 = lua_tolstring(param_1,1,(uint *)0x0);
        iVar3 = luaL_optinteger(param_1,2,0);
        iVar3 = GetNearestEnemy(pcVar4,iVar3);
      }
      goto LAB_00417ec8;
    }
  }
  else {
    local_1c.x = (float)pMVar1->posit_x;
    local_1c.y = (float)pMVar1->posit_y;
    local_1c.z = (float)pMVar1->posit_z;
    pVVar2 = &local_1c;
    local_10 = local_1c.x;
    local_c = local_1c.y;
    local_8 = local_1c.z;
  }
  iVar3 = GetNearestEnemy(pVVar2,(GameObject *)0x0);
LAB_00417ec8:
  PushHandle(param_1,iVar3);
  return 1;
}
