/*
 * Entry: 005c001c
 * Name: check_capture
 * Namespace: Global
 * Signature: int check_capture(MatchState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_capture(MatchState *param_1,int param_2)

{
  int in_EAX;
  int iVar1;
  int in_ECX;
  
  iVar1 = in_EAX + -0x31;
  if (((iVar1 < 0) || (*(int *)(in_ECX + 0xc) <= iVar1)) ||
     (*(int *)(in_ECX + 0x14 + iVar1 * 8) == -1)) {
    iVar1 = luaL_error(*(lua_State **)(in_ECX + 8),"invalid capture index");
  }
  return iVar1;
}
