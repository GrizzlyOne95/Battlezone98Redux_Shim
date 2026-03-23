
void FUN_008396f7(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  lconv *plVar2;
  int iVar3;
  
  plVar2 = localeconv();
  uVar1 = *(undefined1 *)(param_1 + 0x44);
  if (plVar2 == (lconv *)0x0) {
    iVar3 = 0x2e;
  }
  else {
    iVar3 = (int)*plVar2->decimal_point;
  }
  *(char *)(param_1 + 0x44) = (char)iVar3;
  FUN_008388c1(param_1,uVar1,iVar3);
  iVar3 = FUN_0082eb45(**(undefined4 **)(param_1 + 0x3c),param_2);
  if (iVar3 == 0) {
    FUN_008388c1(param_1,*(undefined1 *)(param_1 + 0x44),0x2e);
    FUN_00838ef5(param_1,"malformed number",0x11c);
  }
  return;
}

