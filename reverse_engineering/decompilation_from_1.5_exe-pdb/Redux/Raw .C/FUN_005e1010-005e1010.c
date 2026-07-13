
void __thiscall FUN_005e1010(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_005e10b0();
  iVar2 = FUN_005e10b0(iVar1);
  FUN_005e10d0(iVar2 + param_2);
  iVar2 = FUN_005e10b0();
  if (*(int *)(param_1 + 0x170) < iVar2) {
    FUN_005e10d0(*(undefined4 *)(param_1 + 0x170));
  }
  if (param_2 < 0) {
    iVar2 = FUN_005e10b0();
    if (iVar2 == 0) {
      iVar2 = FUN_00462370();
      if (param_1 == iVar2) {
        FUN_00417c60();
      }
    }
  }
  iVar2 = FUN_005e10b0();
  FUN_006a3730(*(undefined4 *)(param_1 + 0x180),iVar2 - iVar1);
  return;
}

