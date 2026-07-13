/*
 * Entry: 005b5fab
 * Name: lua_rawequal
 * Namespace: Global
 * Signature: int lua_rawequal(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_rawequal(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  plVar2 = index2adr(unaff_ESI,unaff_retaddr);
  if ((plVar1 != &luaO_nilobject_) && (plVar2 != &luaO_nilobject_)) {
    iVar3 = luaO_rawequalObj(plVar1,plVar2);
    return iVar3;
  }
  return 0;
}
