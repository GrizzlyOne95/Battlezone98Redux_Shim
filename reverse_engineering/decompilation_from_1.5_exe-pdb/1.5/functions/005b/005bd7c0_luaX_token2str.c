/*
 * Entry: 005bd7c0
 * Name: luaX_token2str
 * Namespace: Global
 * Signature: char * luaX_token2str(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaX_token2str(LexState *param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  
  if (param_2 < 0x101) {
    iVar1 = iscntrl(param_2);
    if (iVar1 == 0) {
      pcVar2 = "%c";
    }
    else {
      pcVar2 = "char(%d)";
    }
    pcVar2 = luaO_pushfstring(param_1->L,pcVar2);
    return pcVar2;
  }
  return *(char **)("cannot resume non-suspended coroutine" + param_2 * 4 + 0x14);
}
