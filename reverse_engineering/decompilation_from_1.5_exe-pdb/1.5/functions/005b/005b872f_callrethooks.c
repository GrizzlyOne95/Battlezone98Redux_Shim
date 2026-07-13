/*
 * Entry: 005b872f
 * Name: callrethooks
 * Namespace: Global
 * Signature: lua_TValue * callrethooks(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl callrethooks(lua_State *param_1,lua_TValue *param_2)

{
  lua_TValue *plVar1;
  int iVar2;
  int in_EAX;
  lua_State *unaff_ESI;
  
  plVar1 = unaff_ESI->stack;
  luaD_callhook(unaff_ESI,1,-1);
  if (*(char *)((unaff_ESI->ci->func->value).b + 6) == '\0') {
    while (((unaff_ESI->hookmask & 2) != 0 &&
           (iVar2 = unaff_ESI->ci->tailcalls, unaff_ESI->ci->tailcalls = iVar2 + -1, iVar2 != 0))) {
      luaD_callhook(unaff_ESI,4,-1);
    }
  }
  return (lua_TValue *)((int)unaff_ESI->stack + (in_EAX - (int)plVar1));
}
