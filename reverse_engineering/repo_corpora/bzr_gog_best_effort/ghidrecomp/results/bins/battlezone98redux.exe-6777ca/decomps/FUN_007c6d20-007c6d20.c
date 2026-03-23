
undefined4 __thiscall FUN_007c6d20(int param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_007c6320();
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
      if (*(int *)(param_1 + 0x14) == 0) {
        uVar2 = 1;
      }
      else {
        uVar2 = (**(code **)(**(int **)(param_1 + 0x14) + 8))(param_2);
      }
    }
    else {
      uVar2 = (**(code **)(**(int **)(param_1 + 0x10) + 8))(param_2);
    }
  }
  else {
    FUN_007c6980();
    uVar2 = 0;
  }
  return uVar2;
}

