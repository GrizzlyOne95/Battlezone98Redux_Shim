/*
 * Entry: 004192ca
 * Name: UnpackShort
 * Namespace: Global
 * Signature: void UnpackShort(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackShort(char **param_1,lua_State *param_2)

{
  short sVar1;
  undefined4 *in_ECX;
  
  sVar1 = *(short *)*in_ECX;
  *in_ECX = (short *)*in_ECX + 1;
  lua_pushinteger((lua_State *)param_1,(int)sVar1);
  return;
}
