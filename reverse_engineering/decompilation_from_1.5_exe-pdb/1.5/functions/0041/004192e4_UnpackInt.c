/*
 * Entry: 004192e4
 * Name: UnpackInt
 * Namespace: Global
 * Signature: void UnpackInt(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackInt(char **param_1,lua_State *param_2)

{
  int iVar1;
  int *in_ECX;
  
  iVar1 = *(int *)*in_ECX;
  *in_ECX = (int)((int *)*in_ECX + 1);
  lua_pushinteger((lua_State *)param_1,iVar1);
  return;
}
