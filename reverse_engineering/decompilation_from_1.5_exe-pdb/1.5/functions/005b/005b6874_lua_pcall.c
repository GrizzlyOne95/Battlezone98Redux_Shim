/*
 * Entry: 005b6874
 * Name: lua_pcall
 * Namespace: Global
 * Signature: int lua_pcall(lua_State * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_pcall(lua_State *param_1,int param_2,int param_3,int param_4)

{
  lua_TValue *plVar1;
  int in_ECX;
  int iVar2;
  lua_State *unaff_ESI;
  
  if (param_4 == 0) {
    iVar2 = 0;
  }
  else {
    plVar1 = index2adr(unaff_ESI,in_ECX);
    iVar2 = (int)plVar1 - (int)param_1->stack;
  }
  iVar2 = luaD_pcall(param_1,f_call,&stack0xfffffff4,
                     (int)param_1->top + ((param_2 + 1) * -0x10 - (int)param_1->stack),iVar2);
  if (param_3 == -1) {
    if (param_1->ci->top <= param_1->top) {
      param_1->ci->top = param_1->top;
    }
  }
  return iVar2;
}
