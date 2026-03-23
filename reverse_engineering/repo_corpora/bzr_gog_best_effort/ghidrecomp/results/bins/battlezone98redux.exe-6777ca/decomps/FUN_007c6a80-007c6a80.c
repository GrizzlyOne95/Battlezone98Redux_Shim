
undefined4 __thiscall
FUN_007c6a80(int param_1,undefined4 param_2,undefined2 param_3,undefined1 param_4)

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
        uVar2 = (**(code **)(**(int **)(param_1 + 0x14) + 0x10))(param_2,param_3,param_4);
      }
    }
    else {
      uVar2 = (**(code **)(**(int **)(param_1 + 0x10) + 0x10))(param_2,param_3,param_4);
    }
  }
  else {
    FUN_007c6980();
    uVar2 = 0;
  }
  return uVar2;
}

