/*
 * Entry: 005c6147
 * Name: luaK_codeABx
 * Namespace: Global
 * Signature: int luaK_codeABx(FuncState * param_1, OpCode param_2, int param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_codeABx(FuncState *param_1,OpCode param_2,int param_3,uint param_4)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = luaK_code((FuncState *)((param_4 << 8 | param_3) << 6 | param_2),param_1->ls->lastline,
                    unaff_ESI);
  return iVar1;
}
