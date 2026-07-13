/*
 * Entry: 005c0064
 * Name: classend
 * Namespace: Global
 * Signature: char * classend(MatchState * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl classend(MatchState *param_1,char *param_2)

{
  char *in_EAX;
  char *pcVar1;
  char *pcVar2;
  int unaff_EDI;
  
  pcVar1 = in_EAX + 1;
  if (*in_EAX == '%') {
    if (*pcVar1 == '\0') {
      luaL_error(*(lua_State **)(unaff_EDI + 8),"malformed pattern (ends with \'%%\')");
    }
  }
  else {
    if (*in_EAX != '[') {
      return pcVar1;
    }
    pcVar2 = pcVar1;
    if (*pcVar1 == '^') {
      pcVar2 = in_EAX + 2;
    }
    do {
      if (*pcVar2 == '\0') {
        luaL_error(*(lua_State **)(unaff_EDI + 8),"malformed pattern (missing \']\')");
      }
      pcVar1 = pcVar2 + 1;
      if ((*pcVar2 == '%') && (*pcVar1 != '\0')) {
        pcVar1 = pcVar2 + 2;
      }
      pcVar2 = pcVar1;
    } while (*pcVar1 != ']');
  }
  return pcVar1 + 1;
}
