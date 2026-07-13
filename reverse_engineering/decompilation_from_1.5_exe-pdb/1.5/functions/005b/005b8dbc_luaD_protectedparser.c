/*
 * Entry: 005b8dbc
 * Name: luaD_protectedparser
 * Namespace: Global
 * Signature: int luaD_protectedparser(lua_State * param_1, Zio * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaD_protectedparser(lua_State *param_1,Zio *param_2,char *param_3)

{
  int iVar1;
  Zio *local_18;
  void *local_14;
  uint local_c;
  char *local_8;
  
  local_14 = (void *)0x0;
  local_c = 0;
  local_18 = param_2;
  local_8 = param_3;
  iVar1 = luaD_pcall(param_1,f_parser,&local_18,(int)param_1->top - (int)param_1->stack,
                     param_1->errfunc);
  luaM_realloc_(param_1,local_14,local_c,0);
  return iVar1;
}
