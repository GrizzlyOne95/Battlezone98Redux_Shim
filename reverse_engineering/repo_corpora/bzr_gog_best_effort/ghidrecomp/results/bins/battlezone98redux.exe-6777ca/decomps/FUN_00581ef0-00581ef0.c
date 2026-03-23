
void __thiscall FUN_00581ef0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_00611610(param_2);
  iVar1 = FUN_00417c70();
  if (*(int *)(param_1 + 0xc4) == iVar1) {
    if (DAT_025ce77c == 0) {
      if (DAT_025ce778 == 0) {
        *(undefined4 *)(param_1 + 200) = 0;
      }
      else {
        *(int *)(param_1 + 200) = DAT_025ce778;
      }
    }
    else {
      uVar2 = (**(code **)(*(int *)(DAT_025ce77c + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 200) = uVar2;
    }
  }
  return;
}

