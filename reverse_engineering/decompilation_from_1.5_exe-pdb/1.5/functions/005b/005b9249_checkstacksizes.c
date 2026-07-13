/*
 * Entry: 005b9249
 * Name: checkstacksizes
 * Namespace: Global
 * Signature: void checkstacksizes(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl checkstacksizes(lua_State *param_1,lua_TValue *param_2)

{
  lua_TValue *plVar1;
  int iVar2;
  int in_EAX;
  lua_State *unaff_ESI;
  
  plVar1 = unaff_ESI->stack;
  iVar2 = unaff_ESI->size_ci;
  if (iVar2 < 0x4e21) {
    if (((((int)unaff_ESI->ci - (int)unaff_ESI->base_ci) / 0x18) * 4 < iVar2) && (0x10 < iVar2)) {
      luaD_reallocCI(unaff_ESI,iVar2 / 2);
    }
    iVar2 = unaff_ESI->stacksize;
    if (((in_EAX - (int)plVar1 >> 4) * 4 < iVar2) && (0x5a < iVar2)) {
      luaD_reallocstack(unaff_ESI,iVar2 / 2);
    }
  }
  return;
}
