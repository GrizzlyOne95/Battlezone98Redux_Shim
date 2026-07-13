/*
 * Entry: 005c003d
 * Name: capture_to_close
 * Namespace: Global
 * Signature: int capture_to_close(MatchState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl capture_to_close(MatchState *param_1)

{
  int iVar1;
  int in_ECX;
  int *piVar2;
  
  iVar1 = *(int *)(in_ECX + 0xc) + -1;
  if (-1 < iVar1) {
    piVar2 = (int *)(in_ECX + 0x14 + iVar1 * 8);
    do {
      if (*piVar2 == -1) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -2;
    } while (-1 < iVar1);
  }
  iVar1 = luaL_error(*(lua_State **)(in_ECX + 8),"invalid pattern capture");
  return iVar1;
}
