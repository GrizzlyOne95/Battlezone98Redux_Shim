/*
 * Entry: 005c3695
 * Name: new_localvar
 * Namespace: Global
 * Signature: void new_localvar(LexState * param_1, TString * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl new_localvar(LexState *param_1,TString *param_2,int param_3)

{
  FuncState *pFVar1;
  int iVar2;
  LexState *unaff_EBX;
  char *unaff_ESI;
  int unaff_EDI;
  
  pFVar1 = unaff_EBX->fs;
  if (200 < (int)(pFVar1->nactvar + 1 + unaff_EDI)) {
    errorlimit((FuncState *)0xc8,0x62233c,unaff_ESI);
  }
  iVar2 = registerlocalvar(unaff_EBX,(TString *)param_1);
  pFVar1->actvar[(uint)pFVar1->nactvar + unaff_EDI] = (ushort)iVar2;
  return;
}
