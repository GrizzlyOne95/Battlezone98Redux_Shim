/*
 * Entry: 005862a3
 * Name: StringVPrintfWorkerA
 * Namespace: Global
 * Signature: T_HRESULT StringVPrintfWorkerA(char * param_1, uint param_2, uint * param_3, char * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __cdecl
StringVPrintfWorkerA(char *param_1,uint param_2,uint *param_3,char *param_4,char *param_5)

{
  uint uVar1;
  int in_EAX;
  uint uVar2;
  undefined4 uVar3;
  int unaff_EDI;
  
  uVar1 = in_EAX - 1;
  uVar3 = 0;
  uVar2 = vsnprintf();
  if (((int)uVar2 < 0) || (uVar1 < uVar2)) {
    *(undefined1 *)(uVar1 + unaff_EDI) = 0;
    uVar3 = 0x8007007a;
    uVar2 = uVar1;
  }
  else if (uVar2 == uVar1) {
    *(undefined1 *)(uVar1 + unaff_EDI) = 0;
    uVar2 = uVar1;
  }
  if (param_1 != (char *)0x0) {
    *(uint *)param_1 = uVar2;
  }
  return uVar3;
}
