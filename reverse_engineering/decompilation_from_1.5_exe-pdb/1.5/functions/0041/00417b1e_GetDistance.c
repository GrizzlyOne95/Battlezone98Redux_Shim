/*
 * Entry: 00417b1e
 * Name: GetDistance
 * Namespace: Global
 * Signature: int GetDistance(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetDistance(lua_State *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  char *pcVar5;
  undefined4 unaff_EDI;
  float fVar6;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  iVar1 = GetHandle(param_1,1);
  local_8 = iVar1;
  pMVar2 = GetMatrix(param_1,2);
  if (pMVar2 == (MAT_3D *)0x0) {
    pVVar3 = GetVector(param_1,2);
    if (pVVar3 == (VECTOR_3D *)0x0) {
      iVar4 = lua_isstring(param_1,2);
      if (iVar4 == 0) {
        iVar4 = GetHandle(param_1,2);
        fVar6 = GetDistance(iVar1,iVar4);
      }
      else {
        pcVar5 = lua_tolstring(param_1,2,(uint *)0x0);
        iVar4 = luaL_optinteger(param_1,3,0);
        fVar6 = GetDistance(iVar1,pcVar5,iVar4);
      }
      goto LAB_00417bc4;
    }
  }
  else {
    local_20.x = (float)pMVar2->posit_x;
    local_20.y = (float)pMVar2->posit_y;
    local_20.z = (float)pMVar2->posit_z;
    pVVar3 = &local_20;
    iVar1 = local_8;
    local_14 = local_20.x;
    local_10 = local_20.y;
    local_c = local_20.z;
  }
  fVar6 = GetDistance(iVar1,pVVar3);
LAB_00417bc4:
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar6 >> 0x20)));
  return 1;
}
