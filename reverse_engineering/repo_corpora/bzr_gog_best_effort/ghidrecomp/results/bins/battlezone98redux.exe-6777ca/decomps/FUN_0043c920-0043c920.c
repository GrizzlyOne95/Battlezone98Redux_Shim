
undefined4 FUN_0043c920(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    iVar2 = DirectSoundCreate(0,param_1 + 0x18,0);
    if (iVar2 == 0) {
      iVar2 = (**(code **)(**(int **)(param_1 + 0x18) + 0x18))
                        (*(undefined4 *)(param_1 + 0x18),*DAT_02cecefc,3);
      if (iVar2 == 0) {
        uVar1 = 1;
      }
      else {
        FUN_0043c990(param_1);
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

