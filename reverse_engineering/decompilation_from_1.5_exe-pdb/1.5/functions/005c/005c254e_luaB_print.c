/*
 * Entry: 005c254e
 * Name: luaB_print
 * Namespace: Global
 * Signature: int luaB_print(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_print(lua_State *param_1)

{
  int iVar1;
  char *_Str;
  FILE *pFVar2;
  int iVar3;
  
  iVar1 = lua_gettop(param_1);
  lua_getfield(param_1,-0x2712,"tostring");
  iVar3 = 1;
  if (0 < iVar1) {
    do {
      lua_pushvalue(param_1,-1);
      lua_pushvalue(param_1,iVar3);
      lua_call(param_1,1,1);
      _Str = lua_tolstring(param_1,-1,(uint *)0x0);
      if (_Str == (char *)0x0) {
        iVar1 = luaL_error(param_1,"\'tostring\' must return a string to \'print\'");
        return iVar1;
      }
      if (1 < iVar3) {
        pFVar2 = __iob_func();
        fputs("\t",pFVar2 + 1);
      }
      pFVar2 = __iob_func();
      fputs(_Str,pFVar2 + 1);
      lua_settop(param_1,-2);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar1);
  }
  pFVar2 = __iob_func();
  fputs("\n",pFVar2 + 1);
  return 0;
}
