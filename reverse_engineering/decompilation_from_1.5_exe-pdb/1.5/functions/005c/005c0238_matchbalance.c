/*
 * Entry: 005c0238
 * Name: matchbalance
 * Namespace: Global
 * Signature: char * matchbalance(MatchState * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl matchbalance(MatchState *param_1,char *param_2,char *param_3)

{
  char *in_EAX;
  char *pcVar1;
  char *in_ECX;
  int in_EDX;
  int iVar2;
  
  if ((*in_EAX == '\0') || (in_EAX[1] == '\0')) {
    luaL_error(*(lua_State **)(in_EDX + 8),"unbalanced pattern");
  }
  if (*in_ECX == *in_EAX) {
    iVar2 = 1;
    do {
      while( true ) {
        pcVar1 = in_ECX;
        in_ECX = pcVar1 + 1;
        if (*(char **)(in_EDX + 4) <= in_ECX) goto LAB_005c0289;
        if (*in_ECX == in_EAX[1]) break;
        if (*in_ECX == *in_EAX) {
          iVar2 = iVar2 + 1;
        }
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    pcVar1 = pcVar1 + 2;
  }
  else {
LAB_005c0289:
    pcVar1 = (char *)0x0;
  }
  return pcVar1;
}
