/*
 * Entry: 00599fa7
 * Name: StringCchLengthA
 * Namespace: Global
 * Signature: T_HRESULT StringCchLengthA(char * param_1, uint param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StringCchLengthA(char *param_1,uint param_2,uint *param_3)

{
  int iVar1;
  uint unaff_EBP;
  char *unaff_EDI;
  uint *unaff_retaddr;
  
  if ((param_1 == (char *)0x0) || (0x7fffffff < param_2)) {
    iVar1 = -0x7ff8ffa9;
  }
  else {
    iVar1 = StringLengthWorkerA(unaff_EDI,unaff_EBP,unaff_retaddr);
  }
  if ((iVar1 < 0) && (param_3 != (uint *)0x0)) {
    *param_3 = 0;
  }
  return iVar1;
}
