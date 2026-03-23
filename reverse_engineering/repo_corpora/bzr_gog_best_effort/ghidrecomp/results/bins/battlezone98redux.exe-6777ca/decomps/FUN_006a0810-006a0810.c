
undefined1 __thiscall FUN_006a0810(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  
  if (*(int *)(param_2 + 0x1c) == 2) {
    uVar1 = -1 < *(int *)(param_2 + 0x13c);
  }
  else if (*(int *)(param_2 + 0x14) == 0x54555252) {
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_006a07e0(*(undefined4 *)(param_2 + 0x14),param_1);
  }
  return uVar1;
}

