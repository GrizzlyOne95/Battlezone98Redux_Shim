/*
 * Entry: 005c5c8f
 * Name: luaK_concat
 * Namespace: Global
 * Signature: void luaK_concat(FuncState * param_1, int * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_concat(FuncState *param_1,int *param_2,int param_3)

{
  int iVar1;
  int unaff_EBX;
  FuncState *unaff_EDI;
  int unaff_retaddr;
  
  if (param_3 != -1) {
    if (*param_2 == -1) {
      *param_2 = param_3;
      return;
    }
    do {
      iVar1 = getjump(unaff_EDI,unaff_EBX);
    } while (iVar1 != -1);
    fixjump(unaff_EDI,unaff_EBX,unaff_retaddr);
  }
  return;
}
