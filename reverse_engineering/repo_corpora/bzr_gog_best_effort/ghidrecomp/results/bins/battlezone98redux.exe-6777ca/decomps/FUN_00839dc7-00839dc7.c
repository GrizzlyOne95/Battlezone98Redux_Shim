
void FUN_00839dc7(int param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0083cf81(*(undefined4 *)(param_1 + 0x30),param_3);
  param_2[4] = 0xffffffff;
  param_2[5] = 0xffffffff;
  *param_2 = 4;
  param_2[2] = uVar1;
  return;
}

