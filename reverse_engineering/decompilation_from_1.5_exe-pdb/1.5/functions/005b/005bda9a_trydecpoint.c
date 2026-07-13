/*
 * Entry: 005bda9a
 * Name: trydecpoint
 * Namespace: Global
 * Signature: void trydecpoint(LexState * param_1, SemInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl trydecpoint(LexState *param_1,SemInfo *param_2)

{
  char cVar1;
  uint uVar2;
  char cVar3;
  lconv *plVar4;
  int iVar5;
  LexState *unaff_ESI;
  char cVar6;
  LexState *pLVar7;
  
  plVar4 = localeconv();
  cVar1 = unaff_ESI->decpoint;
  uVar2 = (uint)pLVar7 >> 8;
  pLVar7 = (LexState *)CONCAT31((int3)uVar2,cVar1);
  if (plVar4 == (lconv *)0x0) {
    cVar3 = '.';
  }
  else {
    cVar3 = *plVar4->decimal_point;
  }
  unaff_ESI->decpoint = cVar3;
  buffreplace(pLVar7,cVar3,cVar1);
  iVar5 = luaO_str2d(unaff_ESI->buff->buffer,(double *)param_1);
  if (iVar5 == 0) {
    buffreplace((LexState *)(uint)(byte)unaff_ESI->decpoint,'.',cVar6);
    luaX_lexerror(unaff_ESI,"malformed number",0x11c);
  }
  return;
}
