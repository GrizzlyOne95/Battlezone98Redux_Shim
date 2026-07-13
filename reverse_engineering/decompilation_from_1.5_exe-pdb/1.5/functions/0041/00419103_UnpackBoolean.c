/*
 * Entry: 00419103
 * Name: UnpackBoolean
 * Namespace: Global
 * Signature: void UnpackBoolean(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackBoolean(char **param_1,lua_State *param_2)

{
  int *in_EAX;
  
  lua_pushboolean((lua_State *)param_1,(uint)((*(byte *)(*in_EAX + -1) & 0x1f) != 0));
  return;
}
