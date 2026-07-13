/*
 * Entry: 005bd2cd
 * Name: luaZ_openspace
 * Namespace: Global
 * Signature: char * luaZ_openspace(lua_State * param_1, Mbuffer * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaZ_openspace(lua_State *param_1,Mbuffer *param_2,uint param_3)

{
  char *pcVar1;
  
  if (param_2->buffsize < param_3) {
    if (param_3 < 0x20) {
      param_3 = 0x20;
    }
    if (param_3 + 1 < 0xfffffffe) {
      pcVar1 = luaM_realloc_(param_1,param_2->buffer,param_2->buffsize,param_3);
    }
    else {
      pcVar1 = luaM_toobig(param_1);
    }
    param_2->buffer = pcVar1;
    param_2->buffsize = param_3;
  }
  return param_2->buffer;
}
