/*
 * Entry: 0041c091
 * Name: SetCommand
 * Namespace: Global
 * Signature: int SetCommand(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetCommand(lua_State *param_1)

{
  GameObject *pGVar1;
  int iVar2;
  char *pcVar3;
  GameObjectClass *pGVar4;
  MAT_3D *pMVar5;
  VECTOR_3D *pVVar6;
  double dVar7;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  int local_18;
  AiCommand local_14;
  int local_10;
  int local_c;
  float local_8;
  
  local_18 = GetHandle(param_1,1);
  pGVar1 = GameObjectHandle::GetObj(local_18);
  if (pGVar1 != (GameObject *)0x0) {
    local_14 = luaL_checkinteger(param_1,2);
    local_10 = luaL_optinteger(param_1,3,1);
    local_c = GetHandle(param_1,4);
    dVar7 = luaL_optnumber(param_1,6,0.0);
    local_8 = (float)dVar7;
    iVar2 = lua_isstring(param_1,7);
    if (iVar2 == 0) {
      pGVar4 = (GameObjectClass *)0x0;
    }
    else {
      pcVar3 = lua_tolstring(param_1,7,(uint *)0x0);
      pGVar4 = GameObjectClass::Find(pcVar3);
    }
    pMVar5 = GetMatrix(param_1,5);
    if (pMVar5 == (MAT_3D *)0x0) {
      pVVar6 = GetVector(param_1,5);
      if (pVVar6 == (VECTOR_3D *)0x0) {
        iVar2 = lua_isstring(param_1,5);
        if (iVar2 == 0) {
          pcVar3 = (char *)0x0;
        }
        else {
          pcVar3 = lua_tolstring(param_1,5,(uint *)0x0);
        }
        SetCommand(local_18,local_14,local_10,local_c,pcVar3,local_8,(long)pGVar4);
        return 0;
      }
    }
    else {
      local_30.x = (float)pMVar5->posit_x;
      local_30.y = (float)pMVar5->posit_y;
      local_30.z = (float)pMVar5->posit_z;
      pVVar6 = &local_30;
      local_24 = local_30.x;
      local_20 = local_30.y;
      local_1c = local_30.z;
    }
    SetCommand(local_18,local_14,local_10,local_c,pVVar6,local_8,(long)pGVar4);
  }
  return 0;
}
