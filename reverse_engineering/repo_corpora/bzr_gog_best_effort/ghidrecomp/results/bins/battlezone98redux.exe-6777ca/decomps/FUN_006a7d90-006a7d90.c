
int __thiscall FUN_006a7d90(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  uVar1 = FUN_0069d250();
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  uVar1 = FUN_0069d250();
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  *(undefined4 *)(param_1 + 0x40) = param_3;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
  *(undefined8 *)(param_1 + 0x80) = 0x41cdcd6500000000;
  *(undefined8 *)(param_1 + 0x78) = 0xc1cdcd6500000000;
  *(undefined8 *)(param_1 + 0x88) = 0;
  *(undefined8 *)(param_1 + 0x90) = 0;
  FUN_006a7e90();
  return param_1;
}

