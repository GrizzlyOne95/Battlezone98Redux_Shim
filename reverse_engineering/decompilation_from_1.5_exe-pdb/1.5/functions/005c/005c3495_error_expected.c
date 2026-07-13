/*
 * Entry: 005c3495
 * Name: error_expected
 * Namespace: Global
 * Signature: void error_expected(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl error_expected(LexState *param_1,int param_2)

{
  char *pcVar1;
  LexState *unaff_ESI;
  
  luaX_token2str(unaff_ESI,(int)param_1);
  pcVar1 = luaO_pushfstring(unaff_ESI->L,"\'%s\' expected");
  luaX_syntaxerror(unaff_ESI,pcVar1);
  return;
}
