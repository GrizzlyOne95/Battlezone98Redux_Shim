/*
 * Entry: 005c6a34
 * Name: luaK_prefix
 * Namespace: Global
 * Signature: void luaK_prefix(FuncState * param_1, UnOpr param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_prefix(FuncState *param_1,UnOpr param_2,expdesc *param_3)

{
  int iVar1;
  FuncState *unaff_ESI;
  expdesc *unaff_EDI;
  expdesc *peVar2;
  
  peVar2 = (expdesc *)0x5;
  if (param_2 == OPR_MINUS) {
    iVar1 = isnumeral(unaff_EDI);
    if (iVar1 == 0) {
      luaK_exp2anyreg(param_1,param_3);
    }
    codearith((FuncState *)0x12,(OpCode)&stack0xffffffe4,unaff_EDI,peVar2);
  }
  else if (param_2 == OPR_NOT) {
    codenot(unaff_ESI,unaff_EDI);
  }
  else if (param_2 == OPR_LEN) {
    luaK_exp2anyreg(param_1,param_3);
    codearith((FuncState *)0x14,(OpCode)&stack0xffffffe4,(expdesc *)param_1,param_3);
  }
  return;
}
