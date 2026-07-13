/*
 * Entry: 00586208
 * Name: StringLengthWorkerA
 * Namespace: Global
 * Signature: T_HRESULT StringLengthWorkerA(char * param_1, uint param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StringLengthWorkerA(char *param_1,uint param_2,uint *param_3)

{
  char *in_EAX;
  int iVar1;
  int in_EDX;
  int iVar2;
  int *unaff_EDI;
  
  iVar1 = 0;
  iVar2 = in_EDX;
  if (in_EDX != 0) {
    do {
      if (*in_EAX == '\0') break;
      in_EAX = in_EAX + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar2 != 0) goto LAB_00586226;
  }
  iVar1 = -0x7ff8ffa9;
LAB_00586226:
  if (unaff_EDI != (int *)0x0) {
    if (-1 < iVar1) {
      *unaff_EDI = in_EDX - iVar2;
      return iVar1;
    }
    *unaff_EDI = 0;
  }
  return iVar1;
}
