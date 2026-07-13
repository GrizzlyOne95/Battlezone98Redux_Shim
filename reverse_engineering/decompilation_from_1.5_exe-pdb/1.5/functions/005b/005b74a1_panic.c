/*
 * Entry: 005b74a1
 * Name: panic
 * Namespace: Global
 * Signature: int panic(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl panic(lua_State *param_1)

{
  char *pcVar1;
  FILE *pFVar2;
  char *_Format;
  
  pcVar1 = lua_tolstring(param_1,-1,(uint *)0x0);
  _Format = "PANIC: unprotected error in call to Lua API (%s)\n";
  pFVar2 = __iob_func();
  fprintf(pFVar2 + 2,_Format,pcVar1);
  return 0;
}
