/*
 * Entry: 004190ea
 * Name: PackBoolean
 * Namespace: Global
 * Signature: bool PackBoolean(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackBoolean(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  int iVar1;
  int *in_EAX;
  int iVar2;
  
  iVar1 = *in_EAX;
  iVar2 = lua_toboolean((lua_State *)param_1,(int)param_2);
  *(char *)(iVar1 + -1) = *(char *)(iVar1 + -1) + (char)iVar2;
  return true;
}
