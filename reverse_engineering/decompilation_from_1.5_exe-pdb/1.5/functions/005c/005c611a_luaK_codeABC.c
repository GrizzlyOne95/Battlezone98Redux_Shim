/*
 * Entry: 005c611a
 * Name: luaK_codeABC
 * Namespace: Global
 * Signature: int luaK_codeABC(FuncState * param_1, OpCode param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_codeABC(FuncState *param_1,OpCode param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = luaK_code((FuncState *)(((param_4 << 9 | param_5) << 8 | param_3) << 6 | param_2),
                    param_1->ls->lastline,unaff_ESI);
  return iVar1;
}
