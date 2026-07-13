
undefined4 FUN_0043b4a0(int param_1)

{
  undefined4 uVar1;
  
  if (((*(uint *)(param_1 + 0x14) & 2) == 0) || (*(int *)(DAT_00915594 + 8) != 0)) {
    if (((*(uint *)(param_1 + 0x14) & 4) == 0) || (*(int *)(DAT_00915594 + 0xc) != 0)) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

