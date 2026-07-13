/*
 * Entry: 004192fa
 * Name: UnpackDouble
 * Namespace: Global
 * Signature: void UnpackDouble(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackDouble(char **param_1,lua_State *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *in_ECX;
  
  puVar1 = (undefined4 *)*in_ECX;
  uVar2 = *puVar1;
  uVar3 = puVar1[1];
  *in_ECX = (int)(puVar1 + 2);
  lua_pushnumber((lua_State *)param_1,(double)CONCAT44(uVar2,uVar3));
  return;
}
