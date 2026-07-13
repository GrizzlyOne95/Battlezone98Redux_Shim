/*
 * Entry: 00586238
 * Name: StringValidateDestA
 * Namespace: Global
 * Signature: T_HRESULT StringValidateDestA(char * param_1, uint param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __cdecl StringValidateDestA(char *param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  char *in_ECX;
  
  uVar1 = 0;
  if ((in_ECX == (char *)0x0) || (param_1 < in_ECX)) {
    uVar1 = 0x80070057;
  }
  return uVar1;
}
