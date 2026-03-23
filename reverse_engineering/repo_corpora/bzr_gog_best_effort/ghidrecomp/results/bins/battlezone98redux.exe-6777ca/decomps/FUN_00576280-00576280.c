
void __thiscall
FUN_00576280(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  *(undefined4 *)(param_1 + 0x98 + *(int *)(param_1 + 0x90) * 0x1c) = param_2;
  *(undefined4 *)(param_1 + 0x9c + *(int *)(param_1 + 0x90) * 0x1c) = param_3;
  *(undefined4 *)(param_1 + 0xa0 + *(int *)(param_1 + 0x90) * 0x1c) = param_4;
  *(undefined4 *)(param_1 + 0xac + *(int *)(param_1 + 0x90) * 0x1c) = param_5;
  *(undefined4 *)(param_1 + 0xb0 + *(int *)(param_1 + 0x90) * 0x1c) = param_6;
  *(undefined4 *)(param_1 + 0xa4 + *(int *)(param_1 + 0x90) * 0x1c) = param_7;
  *(undefined4 *)(param_1 + 0xa8 + *(int *)(param_1 + 0x90) * 0x1c) = param_8;
  *(int *)(param_1 + 0x90) = (*(int *)(param_1 + 0x90) + 1) % 10;
  if (*(int *)(param_1 + 0x94) < 10) {
    *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + 1;
  }
  return;
}

