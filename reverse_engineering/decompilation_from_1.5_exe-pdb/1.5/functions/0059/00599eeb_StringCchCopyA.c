/*
 * Entry: 00599eeb
 * Name: StringCchCopyA
 * Namespace: Global
 * Signature: T_HRESULT StringCchCopyA(char * param_1, uint param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __cdecl StringCchCopyA(char *param_1,uint param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = 0;
  if ((param_2 == 0) || (0x7fffffff < param_2)) {
    iVar1 = -0x7ff8ffa9;
  }
  if (iVar1 < 0) {
    return iVar1;
  }
  uVar2 = 0;
  if (param_2 != 0) {
    iVar3 = 0x7ffffffe - param_2;
    iVar1 = (int)param_3 - (int)param_1;
    do {
      if ((iVar3 + param_2 == 0) || (param_1[iVar1] == '\0')) break;
      *param_1 = param_1[iVar1];
      param_1 = param_1 + 1;
      param_2 = param_2 - 1;
    } while (param_2 != 0);
    if (param_2 != 0) goto LAB_00599f43;
  }
  param_1 = param_1 + -1;
  uVar2 = 0x8007007a;
LAB_00599f43:
  *param_1 = '\0';
  return uVar2;
}
