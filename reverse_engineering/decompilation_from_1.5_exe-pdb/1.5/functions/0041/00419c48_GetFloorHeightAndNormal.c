/*
 * Entry: 00419c48
 * Name: GetFloorHeightAndNormal
 * Namespace: Global
 * Signature: int GetFloorHeightAndNormal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetFloorHeightAndNormal(lua_State *param_1)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  char *pcVar4;
  lua_State *unaff_EDI;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  GetMatrix(param_1,1);
  pVVar2 = GetVector(param_1,1);
  if (pVVar2 == (VECTOR_3D *)0x0) {
    iVar3 = lua_isstring(param_1,3);
    if (iVar3 == 0) {
      iVar3 = GetHandle(param_1,3);
      pVVar2 = GetPosition(&local_2c,iVar3);
    }
    else {
      pcVar4 = lua_tolstring(param_1,3,(uint *)0x0);
      iVar3 = luaL_optinteger(param_1,4,0);
      pVVar2 = GetPosition(&local_2c,pcVar4,iVar3);
    }
  }
  local_14 = pVVar2->x;
  local_10 = pVVar2->y;
  local_c = pVVar2->z;
  VVar1.y._0_4_ = SUB84((double)local_10,0);
  VVar1.x = (double)local_14;
  VVar1.y._4_4_ = (int)((ulonglong)(double)local_10 >> 0x20);
  VVar1.z._0_4_ = SUB84((double)local_c,0);
  VVar1.z._4_4_ = (int)((ulonglong)(double)local_c >> 0x20);
  Floor_GetFloor(VVar1,&local_8,&local_20);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)local_8 >> 0x20)));
  pVVar2 = NewVector(unaff_EDI);
  pVVar2->x = local_20.x;
  pVVar2->y = local_20.y;
  pVVar2->z = local_20.z;
  return 2;
}
