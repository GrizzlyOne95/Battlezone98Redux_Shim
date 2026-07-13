/*
 * Entry: 005c4589
 * Name: simpleexp
 * Namespace: Global
 * Signature: void simpleexp(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl simpleexp(LexState *param_1,expdesc *param_2)

{
  uchar *puVar1;
  FuncState *pFVar2;
  LexState *in_EAX;
  int iVar3;
  LexState *in_ECX;
  TString *unaff_EBX;
  expdesc *unaff_ESI;
  
  iVar3 = (in_ECX->t).token;
  if (iVar3 < 0x114) {
    if (iVar3 == 0x113) {
      in_EAX->current = 2;
    }
    else {
      if (iVar3 == 0x7b) {
        constructor(param_1,param_2);
        return;
      }
      if (iVar3 == 0x107) {
        in_EAX->current = 3;
      }
      else {
        if (iVar3 == 0x109) {
          luaX_next(in_ECX);
          body(in_EAX,(expdesc *)0x0,(int)in_ECX,(int)unaff_ESI);
          return;
        }
        if (iVar3 != 0x10d) {
LAB_005c4613:
          primaryexp(in_EAX,unaff_ESI);
          return;
        }
        in_EAX->current = 1;
      }
    }
    (in_EAX->t).token = -1;
    *(undefined4 *)&(in_EAX->t).field_0x4 = 0xffffffff;
    in_EAX->lastline = 0;
  }
  else if (iVar3 == 0x117) {
    pFVar2 = in_ECX->fs;
    if (pFVar2->f->is_vararg == '\0') {
      luaX_syntaxerror(in_ECX,"cannot use \'...\' outside a vararg function");
    }
    puVar1 = &pFVar2->f->is_vararg;
    *puVar1 = *puVar1 & 0xfb;
    iVar3 = luaK_codeABC(pFVar2,OP_VARARG,0,1,0);
    (in_EAX->t).token = -1;
    *(undefined4 *)&(in_EAX->t).field_0x4 = 0xffffffff;
    in_EAX->current = 0xe;
    in_EAX->lastline = iVar3;
  }
  else if (iVar3 == 0x11c) {
    (in_EAX->t).token = -1;
    *(undefined4 *)&(in_EAX->t).field_0x4 = 0xffffffff;
    in_EAX->lastline = 0;
    in_EAX->current = 5;
    *(SemInfo *)&in_EAX->lastline = (in_ECX->t).seminfo;
  }
  else {
    if (iVar3 != 0x11e) goto LAB_005c4613;
    codestring((LexState *)&((in_ECX->t).seminfo.ts)->tsv,unaff_ESI,unaff_EBX);
  }
  luaX_next(in_ECX);
  return;
}
