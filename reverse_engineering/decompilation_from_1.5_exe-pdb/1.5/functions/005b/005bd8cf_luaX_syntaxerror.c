/*
 * Entry: 005bd8cf
 * Name: luaX_syntaxerror
 * Namespace: Global
 * Signature: void luaX_syntaxerror(LexState * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_syntaxerror(LexState *param_1,char *param_2)

{
  luaX_lexerror(param_1,param_2,(param_1->t).token);
  return;
}
