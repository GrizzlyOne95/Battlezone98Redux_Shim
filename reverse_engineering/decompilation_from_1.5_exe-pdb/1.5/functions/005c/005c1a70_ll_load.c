/*
 * Entry: 005c1a70
 * Name: ll_load
 * Namespace: Global
 * Signature: void * ll_load(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl ll_load(lua_State *param_1,char *param_2)

{
  HMODULE pHVar1;
  lua_State *unaff_ESI;
  
  pHVar1 = LoadLibraryA((LPCSTR)param_1);
  if (pHVar1 == (HMODULE)0x0) {
    pusherror(unaff_ESI);
  }
  return pHVar1;
}
