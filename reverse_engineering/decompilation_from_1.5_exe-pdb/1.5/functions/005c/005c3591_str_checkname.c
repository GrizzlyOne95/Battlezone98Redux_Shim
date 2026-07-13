/*
 * Entry: 005c3591
 * Name: str_checkname
 * Namespace: Global
 * Signature: TString * str_checkname(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TString * __cdecl str_checkname(LexState *param_1)

{
  TString *pTVar1;
  LexState *in_EAX;
  int unaff_EDI;
  
  if ((in_EAX->t).token != 0x11d) {
    error_expected((LexState *)0x11d,unaff_EDI);
  }
  pTVar1 = (in_EAX->t).seminfo.ts;
  luaX_next(in_EAX);
  return pTVar1;
}
