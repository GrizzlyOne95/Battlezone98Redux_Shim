/*
 * Entry: 005c41e9
 * Name: body
 * Namespace: Global
 * Signature: void body(LexState * param_1, expdesc * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl body(LexState *param_1,expdesc *param_2,int param_3,int param_4)

{
  TString *pTVar1;
  TString *in_ECX;
  FuncState *unaff_EBX;
  int unaff_ESI;
  LexState *unaff_EDI;
  TString *pTVar2;
  char *pcVar3;
  FuncState local_244;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  open_func(unaff_EDI,unaff_EBX);
  (local_244.f)->linedefined = unaff_ESI;
  checknext(unaff_EDI,(int)unaff_EBX);
  if (param_2 != (expdesc *)0x0) {
    pcVar3 = "self";
    pTVar2 = in_ECX;
    pTVar1 = luaX_newstring((LexState *)&in_ECX->tsv,"self",4);
    new_localvar((LexState *)&pTVar1->tsv,pTVar2,(int)pcVar3);
    adjustlocalvars(unaff_EDI,(int)unaff_EBX);
  }
  parlist(unaff_EDI);
  checknext(unaff_EDI,(int)unaff_EBX);
  chunk((LexState *)&in_ECX->tsv);
  (local_244.f)->lastlinedefined = *(int *)&(in_ECX->tsv).tt;
  check_match((LexState *)0x106,0x109,(int)unaff_EDI,(int)unaff_EBX);
  close_func((LexState *)&in_ECX->tsv);
  pushclosure((LexState *)&in_ECX->tsv,&local_244,(expdesc *)param_1);
  return;
}
