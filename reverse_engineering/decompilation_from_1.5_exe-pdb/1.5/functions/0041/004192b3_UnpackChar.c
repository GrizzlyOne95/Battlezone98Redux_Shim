/*
 * Entry: 004192b3
 * Name: UnpackChar
 * Namespace: Global
 * Signature: void UnpackChar(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackChar(char **param_1,lua_State *param_2)

{
  char cVar1;
  undefined4 *in_ECX;
  
  cVar1 = *(char *)*in_ECX;
  *in_ECX = (char *)*in_ECX + 1;
  lua_pushinteger((lua_State *)param_1,(int)cVar1);
  return;
}
