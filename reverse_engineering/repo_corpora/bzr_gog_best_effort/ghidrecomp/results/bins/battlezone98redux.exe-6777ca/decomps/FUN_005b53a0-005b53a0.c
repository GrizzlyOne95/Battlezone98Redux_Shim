
undefined4 FUN_005b53a0(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x48) == 2) {
    uVar1 = 0;
  }
  else if (*(int *)(param_1 + 0x48) == 3) {
    uVar1 = 1;
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

