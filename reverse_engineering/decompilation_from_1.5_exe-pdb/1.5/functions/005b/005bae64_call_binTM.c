/*
 * Entry: 005bae64
 * Name: call_binTM
 * Namespace: Global
 * Signature: int call_binTM(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4, TMS param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
call_binTM(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4,
          TMS param_5)

{
  lua_TValue *plVar1;
  lua_TValue *unaff_EBP;
  lua_TValue *unaff_retaddr;
  
  plVar1 = luaT_gettmbyobj(param_1,param_2,param_5);
  if (plVar1->tt == 0) {
    plVar1 = luaT_gettmbyobj(param_1,param_3,param_5);
    if (plVar1->tt == 0) {
      return 0;
    }
  }
  callTMres(param_1,plVar1,unaff_EBP,unaff_retaddr,(lua_TValue *)param_1);
  return 1;
}
