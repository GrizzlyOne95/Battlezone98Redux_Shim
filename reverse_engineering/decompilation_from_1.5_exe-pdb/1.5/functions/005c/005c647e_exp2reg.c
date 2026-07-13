/*
 * Entry: 005c647e
 * Name: exp2reg
 * Namespace: Global
 * Signature: void exp2reg(FuncState * param_1, expdesc * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl exp2reg(FuncState *param_1,expdesc *param_2,int param_3)

{
  FuncState *pFVar1;
  int *in_EAX;
  int iVar2;
  FuncState *in_ECX;
  int unaff_EBX;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  FuncState *pFVar3;
  FuncState *pFVar4;
  int local_c;
  int local_8;
  
  discharge2reg(unaff_EDI,unaff_ESI,unaff_EBX);
  if (*in_EAX == 10) {
    luaK_concat(in_ECX,in_EAX + 4,in_EAX[2]);
  }
  if (in_EAX[4] == in_EAX[5]) goto LAB_005c654d;
  local_8 = -1;
  local_c = -1;
  iVar2 = need_value(in_ECX,(int)unaff_EDI);
  if (iVar2 == 0) {
    iVar2 = need_value(in_ECX,(int)unaff_EDI);
    if (iVar2 != 0) goto LAB_005c64d5;
  }
  else {
LAB_005c64d5:
    if (*in_EAX == 10) {
      iVar2 = -1;
    }
    else {
      iVar2 = luaK_jump(in_ECX);
    }
    in_ECX->lasttarget = in_ECX->pc;
    local_8 = luaK_codeABC(in_ECX,OP_LOADBOOL,(int)param_1,0,1);
    in_ECX->lasttarget = in_ECX->pc;
    local_c = luaK_codeABC(in_ECX,OP_LOADBOOL,(int)param_1,1,0);
    luaK_patchtohere(in_ECX,iVar2);
  }
  pFVar1 = (FuncState *)in_ECX->pc;
  in_ECX->lasttarget = (int)pFVar1;
  pFVar3 = pFVar1;
  pFVar4 = param_1;
  patchlistaux(pFVar1,(int)param_1,local_8,(int)unaff_EDI,(int)unaff_ESI);
  patchlistaux(pFVar1,(int)param_1,local_c,(int)pFVar3,(int)pFVar4);
LAB_005c654d:
  in_EAX[4] = -1;
  in_EAX[5] = -1;
  in_EAX[2] = (int)param_1;
  *in_EAX = 0xc;
  return;
}
