
void FUN_00838ffd(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 4);
  piVar1 = (int *)(param_1 + 0x20);
  if (*piVar1 == 0x11f) {
    uVar2 = FUN_008389c5(param_1,param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
  }
  else {
    *(int *)(param_1 + 0x10) = *piVar1;
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x2c);
    *piVar1 = 0x11f;
  }
  return;
}

