/*
 * Entry: 004190e5
 * Name: UnpackNil
 * Namespace: Global
 * Signature: void UnpackNil(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackNil(char **param_1,lua_State *param_2)

{
  char *pcVar1;
  
  pcVar1 = param_1[2];
  pcVar1[8] = '\0';
  pcVar1[9] = '\0';
  pcVar1[10] = '\0';
  pcVar1[0xb] = '\0';
  param_1[2] = param_1[2] + 0x10;
  return;
}
