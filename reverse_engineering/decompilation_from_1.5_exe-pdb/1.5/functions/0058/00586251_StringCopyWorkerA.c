/*
 * Entry: 00586251
 * Name: StringCopyWorkerA
 * Namespace: Global
 * Signature: T_HRESULT StringCopyWorkerA(char * param_1, uint param_2, uint * param_3, char * param_4, uint param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __cdecl
StringCopyWorkerA(char *param_1,uint param_2,uint *param_3,char *param_4,uint param_5)

{
  int in_EAX;
  int iVar1;
  char *in_ECX;
  int in_EDX;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = 0;
  if (in_EAX != 0) {
    iVar2 = param_2 - (int)in_ECX;
    do {
      if ((in_EDX == 0) || (in_ECX[iVar2] == '\0')) break;
      *in_ECX = in_ECX[iVar2];
      in_ECX = in_ECX + 1;
      in_EDX = in_EDX + -1;
      iVar1 = iVar1 + 1;
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
    if (in_EAX != 0) goto LAB_0058628f;
  }
  in_ECX = in_ECX + -1;
  iVar1 = iVar1 + -1;
  local_8 = 0x8007007a;
LAB_0058628f:
  *in_ECX = '\0';
  if (param_1 != (char *)0x0) {
    *(int *)param_1 = iVar1;
  }
  return local_8;
}
