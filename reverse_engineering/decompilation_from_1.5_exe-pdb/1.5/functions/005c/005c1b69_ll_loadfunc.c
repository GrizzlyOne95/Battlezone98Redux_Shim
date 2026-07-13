/*
 * Entry: 005c1b69
 * Name: ll_loadfunc
 * Namespace: Global
 * Signature: int ll_loadfunc(lua_State * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ll_loadfunc(lua_State *param_1,char *param_2,char *param_3)

{
  lua_State *in_EAX;
  void **ppvVar1;
  HMODULE pHVar2;
  _func___cdecl_int_lua_State_ptr *p_Var3;
  int iVar4;
  lua_State *unaff_EDI;
  
  ppvVar1 = ll_register(param_1,(char *)unaff_EDI);
  if (*ppvVar1 == (void *)0x0) {
    pHVar2 = LoadLibraryA((LPCSTR)param_1);
    if (pHVar2 == (HMODULE)0x0) {
      pusherror(unaff_EDI);
    }
    *ppvVar1 = pHVar2;
    if (pHVar2 == (HMODULE)0x0) {
      return 1;
    }
  }
  p_Var3 = (_func___cdecl_int_lua_State_ptr *)GetProcAddress(*ppvVar1,param_2);
  if (p_Var3 == (_func___cdecl_int_lua_State_ptr *)0x0) {
    pusherror(unaff_EDI);
    iVar4 = 2;
  }
  else {
    lua_pushcclosure(in_EAX,p_Var3,0);
    iVar4 = 0;
  }
  return iVar4;
}
