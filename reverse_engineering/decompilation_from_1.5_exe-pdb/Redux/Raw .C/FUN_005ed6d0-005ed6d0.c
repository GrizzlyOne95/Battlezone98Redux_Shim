
void __thiscall FUN_005ed6d0(int param_1,undefined4 *param_2,int *param_3)

{
  undefined4 uVar1;
  
  *param_3 = *param_3 + 8;
  if (*(int *)(param_1 + 0x210) == 0) {
    *(undefined1 *)(param_2 + 1) = 0;
  }
  else if (*(int *)(param_1 + 0x210) == 1) {
    *(undefined1 *)(param_2 + 1) = 1;
  }
  else if (*(int *)(param_1 + 0x210) == 2) {
    *(undefined1 *)(param_2 + 1) = 2;
  }
  else if (*(int *)(param_1 + 0x210) == 3) {
    *(undefined1 *)(param_2 + 1) = 3;
  }
  if (*(int *)(param_1 + 0x2e8) == 0) {
    *param_2 = 0;
  }
  else {
    uVar1 = FUN_004b9a90();
    *param_2 = uVar1;
  }
  FUN_004ef640(param_2 + 2,param_3);
  return;
}

