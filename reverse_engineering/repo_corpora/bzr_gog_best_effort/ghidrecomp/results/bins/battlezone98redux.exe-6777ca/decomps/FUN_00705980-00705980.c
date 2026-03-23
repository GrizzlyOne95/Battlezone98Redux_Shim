
undefined4 __thiscall FUN_00705980(int param_1,undefined1 *param_2,uint param_3)

{
  undefined4 uVar1;
  
  if ((param_3 == 0) || (*(int *)(param_1 + 0x18) == 0)) {
    uVar1 = 0;
  }
  else if (param_3 < 2) {
    if (*(int *)(param_1 + 0x18) == 2) {
      *(undefined1 *)(param_1 + 0xc) = *param_2;
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
      uVar1 = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0xd) = *param_2;
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
      uVar1 = 1;
    }
  }
  else if (*(int *)(param_1 + 0x18) == 2) {
    *(undefined1 *)(param_1 + 0xc) = *param_2;
    *(undefined1 *)(param_1 + 0xd) = param_2[1];
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -2;
    uVar1 = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0xd) = *param_2;
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
    uVar1 = 1;
  }
  return uVar1;
}

