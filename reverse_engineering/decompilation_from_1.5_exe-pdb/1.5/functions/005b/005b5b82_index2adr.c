/*
 * Entry: 005b5b82
 * Name: index2adr
 * Namespace: Global
 * Signature: lua_TValue * index2adr(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl index2adr(lua_State *param_1,int param_2)

{
  int iVar1;
  int in_EAX;
  lua_TValue *plVar2;
  int in_EDX;
  
  if (in_EAX < 1) {
    if (-10000 < in_EAX) {
      return (lua_TValue *)(in_EAX * 0x10 + *(int *)(in_EDX + 8));
    }
    if (in_EAX != -0x2712) {
      if (in_EAX == -0x2711) {
        (((lua_TValue *)(in_EDX + 0x58))->value).gc =
             *(GCObject **)(**(int **)(*(int *)(in_EDX + 0x14) + 4) + 0xc);
        *(undefined4 *)(in_EDX + 0x60) = 5;
        return (lua_TValue *)(in_EDX + 0x58);
      }
      if (in_EAX != -10000) {
        iVar1 = **(int **)(*(int *)(in_EDX + 0x14) + 4);
        if (-0x2712 - in_EAX <= (int)(uint)*(byte *)(iVar1 + 7)) {
          return (lua_TValue *)((-0x2712 - in_EAX) * 0x10 + 8 + iVar1);
        }
        return &luaO_nilobject_;
      }
      return (lua_TValue *)(*(int *)(in_EDX + 0x10) + 0x60);
    }
    plVar2 = (lua_TValue *)(in_EDX + 0x48);
  }
  else {
    plVar2 = (lua_TValue *)(*(int *)(in_EDX + 0xc) + -0x10 + in_EAX * 0x10);
    if (*(lua_TValue **)(in_EDX + 8) <= plVar2) {
      return &luaO_nilobject_;
    }
  }
  return plVar2;
}
