
uint __thiscall FUN_00613b70(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 7) {
    if (*(int *)(*(int *)(param_1 + 0x38) + 8) == 6) {
      uVar1 = FUN_00613ad0();
    }
    else {
      uVar1 = FUN_00583430(7);
    }
  }
  else if (param_2 == 8) {
    if ((*(int *)(param_1 + 0x24) == 0) && (*(int *)(*(int *)(param_1 + 0x38) + 8) != 4)) {
      return param_1 & 0xffffff00;
    }
    uVar1 = FUN_00583430(8);
  }
  else if (param_2 == 0x10) {
    uVar1 = FUN_00583a50();
  }
  else {
    uVar1 = FUN_00583430(param_2);
  }
  return uVar1;
}

