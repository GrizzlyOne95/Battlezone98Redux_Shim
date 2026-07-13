/*
 * Entry: 005c353b
 * Name: check_match
 * Namespace: Global
 * Signature: void check_match(LexState * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl check_match(LexState *param_1,int param_2,int param_3,int param_4)

{
  LexState *in_EAX;
  int iVar1;
  char *pcVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  iVar1 = testnext(param_1,unaff_ESI);
  if (iVar1 == 0) {
    if (unaff_EDI == in_EAX->linenumber) {
      error_expected(param_1,unaff_ESI);
      return;
    }
    luaX_token2str(in_EAX,param_2);
    luaX_token2str(in_EAX,(int)param_1);
    pcVar2 = luaO_pushfstring(in_EAX->L,"\'%s\' expected (to close \'%s\' at line %d)");
    luaX_syntaxerror(in_EAX,pcVar2);
  }
  return;
}
