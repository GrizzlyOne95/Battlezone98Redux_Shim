/*
 * Entry: 005c512e
 * Name: funcstat
 * Namespace: Global
 * Signature: void funcstat(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl funcstat(LexState *param_1,int param_2)

{
  LexState *unaff_EBX;
  expdesc *unaff_ESI;
  LexState *unaff_EDI;
  bool bVar1;
  expdesc local_34;
  expdesc local_1c;
  
  luaX_next(unaff_EBX);
  singlevar(unaff_EDI,unaff_ESI);
  while ((unaff_EBX->t).token == 0x2e) {
    field((LexState *)&local_1c,(expdesc *)unaff_EDI);
  }
  bVar1 = (unaff_EBX->t).token == 0x3a;
  if (bVar1) {
    field((LexState *)&local_1c,(expdesc *)unaff_EDI);
  }
  body((LexState *)&local_34,(expdesc *)(uint)bVar1,(int)unaff_EDI,(int)unaff_ESI);
  luaK_storevar(unaff_EBX->fs,&local_1c,&local_34);
  luaK_fixline(unaff_EBX->fs,(int)param_1);
  return;
}
