/*
 * Entry: 005c62a8
 * Name: condjump
 * Namespace: Global
 * Signature: int condjump(FuncState * param_1, OpCode param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl condjump(FuncState *param_1,OpCode param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  luaK_codeABC(param_1,param_2,param_3,param_4,param_5);
  iVar1 = luaK_jump(param_1);
  return iVar1;
}
