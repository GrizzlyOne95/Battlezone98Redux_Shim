/*
 * Entry: 00599f4e
 * Name: StringCchPrintfA
 * Namespace: Global
 * Signature: T_HRESULT StringCchPrintfA(char * param_1, uint param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StringCchPrintfA(char *param_1,uint param_2,char *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  if ((param_2 == 0) || (0x7fffffff < param_2)) {
    iVar2 = -0x7ff8ffa9;
  }
  if (-1 < iVar2) {
    uVar1 = param_2 - 1;
    iVar2 = 0;
    uVar3 = vsnprintf(param_1,uVar1,param_3,&stack0x00000010);
    if (((int)uVar3 < 0) || (uVar1 < uVar3)) {
      param_1[uVar1] = '\0';
      iVar2 = -0x7ff8ff86;
    }
    else if (uVar3 == uVar1) {
      param_1[uVar1] = '\0';
    }
  }
  return iVar2;
}
