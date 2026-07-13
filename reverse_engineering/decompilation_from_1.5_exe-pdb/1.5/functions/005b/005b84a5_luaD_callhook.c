/*
 * Entry: 005b84a5
 * Name: luaD_callhook
 * Namespace: Global
 * Signature: void luaD_callhook(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl luaD_callhook(lua_State *param_1,int param_2,int param_3)

{
  _func___cdecl_void_lua_State_ptr_lua_Debug_ptr *p_Var1;
  lua_TValue *plVar2;
  lua_TValue *plVar3;
  lua_TValue *plVar4;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var1 = param_1->hook;
  if ((p_Var1 != (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x0) &&
     (param_1->allowhook != '\0')) {
    plVar2 = param_1->stack;
    plVar3 = param_1->top;
    plVar4 = param_1->ci->top;
    local_6c.event = param_2;
    local_6c.currentline = param_3;
    if (param_2 == 4) {
      local_6c.i_ci = 0;
    }
    else {
      local_6c.i_ci = ((int)param_1->ci - (int)param_1->base_ci) / 0x18;
    }
    if ((int)param_1->stack_last - (int)param_1->top < 0x141) {
      luaD_growstack(param_1,0x14);
    }
    param_1->ci->top = param_1->top + 0x14;
    param_1->allowhook = '\0';
    (*p_Var1)(param_1,&local_6c);
    param_1->allowhook = '\x01';
    param_1->ci->top = (lua_TValue *)((int)param_1->stack + ((int)plVar4 - (int)plVar2));
    param_1->top = (lua_TValue *)((int)param_1->stack + ((int)plVar3 - (int)plVar2));
  }
  return;
}
