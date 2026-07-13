/*
 * Entry: 005bd5ef
 * Name: luaU_dump
 * Namespace: Global
 * Signature: int luaU_dump(lua_State * param_1, Proto * param_2, _func___cdecl_int_lua_State_ptr_void_ptr_uint_void_ptr * param_3, void * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
luaU_dump(lua_State *param_1,Proto *param_2,
         _func___cdecl_int_lua_State_ptr_void_ptr_uint_void_ptr *param_3,void *param_4,int param_5)

{
  DumpState *pDVar1;
  DumpState local_28;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_28.status = 0;
  local_28.L = param_1;
  local_28.strip = param_5;
  pDVar1 = (DumpState *)local_14;
  local_28.writer = param_3;
  local_28.data = param_4;
  luaU_header((char *)pDVar1);
  DumpBlock(local_14,0xc,pDVar1);
  DumpFunction(param_2,(TString *)0x0,&local_28);
  return local_28.status;
}
