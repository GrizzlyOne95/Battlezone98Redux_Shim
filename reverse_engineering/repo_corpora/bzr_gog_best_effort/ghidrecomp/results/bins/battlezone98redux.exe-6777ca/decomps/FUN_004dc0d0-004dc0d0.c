
void __thiscall FUN_004dc0d0(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0046d060();
  if (0 < iVar1) {
    if (((param_1 == DAT_00917afc) && (param_2 < 1)) && (iVar1 = FUN_004d9b00(), iVar1 != 0)) {
      return;
    }
    iVar1 = FUN_00417c80();
    uVar2 = FUN_0046d060(iVar1 + param_2);
    uVar2 = FUN_0046b550(uVar2);
    FUN_004a7700(uVar2);
  }
  return;
}

