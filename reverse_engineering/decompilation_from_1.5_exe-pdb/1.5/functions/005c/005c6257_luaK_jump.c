/*
 * Entry: 005c6257
 * Name: luaK_jump
 * Namespace: Global
 * Signature: int luaK_jump(FuncState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_jump(FuncState *param_1)

{
  int iVar1;
  FuncState *pFVar2;
  
  pFVar2 = param_1;
  iVar1 = param_1->jpc;
  param_1->jpc = -1;
  param_1 = (FuncState *)luaK_codeABx(param_1,OP_JMP,0,0x1fffe);
  luaK_concat(pFVar2,(int *)&param_1,iVar1);
  return (int)param_1;
}
