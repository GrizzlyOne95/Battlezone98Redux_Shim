/*
 * Entry: 005b7244
 * Name: errfile
 * Namespace: Global
 * Signature: int errfile(lua_State * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl errfile(lua_State *param_1,char *param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = _errno();
  strerror(*piVar1);
  lua_tolstring(param_1,param_3,(uint *)0x0);
  lua_pushfstring(param_1,"cannot %s %s: %s");
  lua_remove(param_1,param_3);
  return 6;
}
