/*
 * Entry: 0041ceb0
 * Name: ObjectsInRange
 * Namespace: Global
 * Signature: int ObjectsInRange(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjectsInRange(lua_State *param_1)

{
  MAT_3D *pMVar1;
  int iVar2;
  char *pcVar3;
  VECTOR_3D *pVVar4;
  undefined4 unaff_EDI;
  double dVar5;
  lua_State *plVar6;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  float local_8;
  
  dVar5 = luaL_optnumber(param_1,1,450.0);
  local_8 = (float)dVar5;
  pMVar1 = GetMatrix(param_1,2);
  if (pMVar1 == (MAT_3D *)0x0) {
    pVVar4 = GetVector(param_1,2);
    if (pVVar4 == (VECTOR_3D *)0x0) {
      iVar2 = lua_isstring(param_1,2);
      if (iVar2 == 0) {
        iVar2 = GetHandle(param_1,2);
        pVVar4 = GetPosition(&local_20,iVar2);
      }
      else {
        pcVar3 = lua_tolstring(param_1,2,(uint *)0x0);
        iVar2 = luaL_optinteger(param_1,3,0);
        pVVar4 = GetPosition(&local_20,pcVar3,iVar2);
      }
    }
  }
  else {
    pVVar4 = &local_20;
    local_20.x = (float)pMVar1->posit_x;
    local_20.y = (float)pMVar1->posit_y;
    local_20.z = (float)pMVar1->posit_z;
  }
  local_14 = pVVar4->x;
  fStack_10 = pVVar4->y;
  fStack_c = pVVar4->z;
  plVar6 = param_1;
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)local_8 >> 0x20)));
  pVVar4 = NewVector(plVar6);
  pVVar4->x = local_14;
  pVVar4->y = fStack_10;
  pVVar4->z = fStack_c;
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,ObjectsInRangeNext,3);
  return 1;
}
