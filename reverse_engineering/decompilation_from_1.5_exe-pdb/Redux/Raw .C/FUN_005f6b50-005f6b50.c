
void __thiscall FUN_005f6b50(int param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_005fa6a0(param_2,param_3);
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined1 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0x43160000;
  *(undefined4 *)(param_1 + 0x74) = 0;
  FUN_00466be0(*(undefined4 *)(param_1 + 0x34),param_1 + 0x68,param_1 + 0x6c,param_1 + 0x70,
               param_1 + 0x74);
  *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x6c) / *(float *)(param_1 + 0x70);
  *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x70) / *(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) * *(float *)(param_1 + 0x68);
  *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) * *(float *)(param_1 + 0x6c);
  return;
}

