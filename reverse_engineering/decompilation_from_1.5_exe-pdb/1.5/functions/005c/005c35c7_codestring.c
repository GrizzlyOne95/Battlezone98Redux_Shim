/*
 * Entry: 005c35c7
 * Name: codestring
 * Namespace: Global
 * Signature: void codestring(LexState * param_1, expdesc * param_2, TString * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl codestring(LexState *param_1,expdesc *param_2,TString *param_3)

{
  int in_EAX;
  int iVar1;
  undefined4 *unaff_ESI;
  
  iVar1 = luaK_stringK(*(FuncState **)(in_EAX + 0x30),(TString *)param_1);
  unaff_ESI[4] = 0xffffffff;
  unaff_ESI[5] = 0xffffffff;
  *unaff_ESI = 4;
  unaff_ESI[2] = iVar1;
  return;
}
