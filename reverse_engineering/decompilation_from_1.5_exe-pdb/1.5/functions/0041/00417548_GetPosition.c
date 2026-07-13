/*
 * Entry: 00417548
 * Name: GetPosition
 * Namespace: Global
 * Signature: int GetPosition(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPosition(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  VECTOR_3D *pVVar3;
  lua_State *unaff_EDI;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  iVar1 = lua_isstring(param_1,1);
  if (iVar1 == 0) {
    iVar1 = GetHandle(param_1,1);
    pVVar3 = GetPosition(&local_1c,iVar1);
  }
  else {
    pcVar2 = luaL_checklstring(param_1,1,(uint *)0x0);
    iVar1 = luaL_optinteger(param_1,2,0);
    pVVar3 = GetPosition(&local_1c,pcVar2,iVar1);
  }
  local_10 = pVVar3->x;
  fStack_c = pVVar3->y;
  fStack_8 = pVVar3->z;
  pVVar3 = NewVector(unaff_EDI);
  pVVar3->x = local_10;
  pVVar3->y = fStack_c;
  pVVar3->z = fStack_8;
  return 1;
}
