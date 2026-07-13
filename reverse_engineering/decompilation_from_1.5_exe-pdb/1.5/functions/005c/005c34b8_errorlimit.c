/*
 * Entry: 005c34b8
 * Name: errorlimit
 * Namespace: Global
 * Signature: void errorlimit(FuncState * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl errorlimit(FuncState *param_1,int param_2,char *param_3)

{
  char *pcVar1;
  int *unaff_ESI;
  
  if (*(int *)(*unaff_ESI + 0x3c) == 0) {
    pcVar1 = luaO_pushfstring((lua_State *)unaff_ESI[4],"main function has more than %d %s");
  }
  else {
    pcVar1 = luaO_pushfstring((lua_State *)unaff_ESI[4],"function at line %d has more than %d %s");
  }
  luaX_lexerror((LexState *)unaff_ESI[3],pcVar1,0);
  return;
}
