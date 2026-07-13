/*
 * Entry: 005c637e
 * Name: code_label
 * Namespace: Global
 * Signature: int code_label(FuncState * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl code_label(FuncState *param_1,int param_2,int param_3,int param_4)

{
  FuncState *in_EAX;
  int iVar1;
  
  in_EAX->lasttarget = in_EAX->pc;
  iVar1 = luaK_codeABC(in_EAX,OP_LOADBOOL,(int)param_1,param_2,param_3);
  return iVar1;
}
