
void __thiscall
FUN_004c73b0(int param_1,ushort param_2,ushort param_3,undefined2 param_4,int param_5,int param_6)

{
  DAT_02cc40b8 = 1;
  if (param_5 != 0) {
    param_2 = param_2 | 0x8000;
  }
  if (param_6 != 0) {
    param_3 = param_3 | 0x8000;
  }
  *(ushort *)(param_1 + 0x4460 + *(int *)(param_1 + 0x415c) * 6) = param_2;
  *(ushort *)(param_1 + 0x4462 + *(int *)(param_1 + 0x415c) * 6) = param_3;
  *(undefined2 *)(param_1 + 0x4464 + *(int *)(param_1 + 0x415c) * 6) = param_4;
  *(int *)(param_1 + 0x4154) = *(int *)(param_1 + 0x4154) + 1;
  *(uint *)(param_1 + 0x415c) = *(int *)(param_1 + 0x415c) + 1U & 0x3fff;
  if (0x3fff < *(int *)(param_1 + 0x4154)) {
    *(undefined4 *)(param_1 + 0x4154) = 0x3fff;
    *(uint *)(param_1 + 0x4158) = *(int *)(param_1 + 0x415c) + 1U & 0x3fff;
  }
  return;
}

