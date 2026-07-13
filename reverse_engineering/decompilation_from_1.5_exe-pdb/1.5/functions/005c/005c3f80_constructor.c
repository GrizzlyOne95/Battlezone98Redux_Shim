/*
 * Entry: 005c3f80
 * Name: constructor
 * Namespace: Global
 * Signature: void constructor(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl constructor(LexState *param_1,expdesc *param_2)

{
  expdesc *in_EAX;
  int iVar1;
  int iVar2;
  LexState *in_ECX;
  FuncState *pFVar3;
  ConsControl *unaff_ESI;
  uint *puVar4;
  LexState *unaff_EDI;
  expdesc local_38;
  expdesc *local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  FuncState *local_8;
  
  pFVar3 = in_ECX->fs;
  local_c = in_ECX->linenumber;
  local_8 = pFVar3;
  local_10 = luaK_codeABC(pFVar3,OP_NEWTABLE,0,0,0);
  in_EAX->t = -1;
  in_EAX->f = -1;
  in_EAX->k = VRELOCABLE;
  (in_EAX->u).s.info = local_10;
  local_14 = 0;
  local_1c = 0;
  local_18 = 0;
  local_38.t = -1;
  local_38.f = -1;
  local_38.k = VVOID;
  local_38.u.s.info = 0;
  local_20 = in_EAX;
  luaK_exp2nextreg(in_ECX->fs,in_EAX);
  checknext(unaff_EDI,(int)unaff_ESI);
  do {
    do {
      if ((in_ECX->t).token == 0x7d) goto LAB_005c407d;
      if (local_38.k != VVOID) {
        luaK_exp2nextreg(pFVar3,&local_38);
        local_38.k = VVOID;
        if (local_14 == 0x32) {
          luaK_setlist(pFVar3,(local_20->u).s.info,local_18,0x32);
          local_14 = 0;
        }
      }
      iVar1 = (in_ECX->t).token;
      if (iVar1 == 0x5b) {
LAB_005c4050:
        recfield(in_ECX,(ConsControl *)unaff_EDI);
        pFVar3 = local_8;
      }
      else {
        if (iVar1 == 0x11d) {
          luaX_lookahead(in_ECX);
          if ((in_ECX->lookahead).token == 0x3d) goto LAB_005c4050;
        }
        listfield(unaff_EDI,unaff_ESI);
      }
      iVar1 = testnext((LexState *)0x2c,(int)unaff_EDI);
    } while (iVar1 != 0);
    iVar1 = testnext((LexState *)0x3b,(int)unaff_EDI);
  } while (iVar1 != 0);
LAB_005c407d:
  check_match((LexState *)0x7d,0x7b,(int)unaff_EDI,(int)unaff_ESI);
  if (local_14 != 0) {
    if ((local_38.k == VCALL) || (local_38.k == VVARARG)) {
      luaK_setreturns(pFVar3,&local_38,-1);
      luaK_setlist(pFVar3,(local_20->u).s.info,local_18,-1);
      local_18 = local_18 - 1;
    }
    else {
      if (local_38.k != VVOID) {
        luaK_exp2nextreg(pFVar3,&local_38);
      }
      luaK_setlist(pFVar3,(local_20->u).s.info,local_18,local_14);
    }
  }
  iVar1 = local_10;
  puVar4 = pFVar3->f->code + local_10;
  iVar2 = luaO_int2fb(local_18);
  *puVar4 = iVar2 << 0x17 | *puVar4 & 0x7fffff;
  puVar4 = pFVar3->f->code + iVar1;
  iVar1 = luaO_int2fb(local_1c);
  *puVar4 = *puVar4 ^ (iVar1 << 0xe ^ *puVar4) & 0x7fc000;
  return;
}
