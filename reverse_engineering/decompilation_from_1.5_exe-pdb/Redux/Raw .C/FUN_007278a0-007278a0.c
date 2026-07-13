
int __thiscall FUN_007278a0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_0071e950(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x70) = *param_3;
  *(undefined4 *)(param_1 + 0x74) = uVar1;
  *(undefined4 *)(param_1 + 0x78) = *param_4;
  return param_1;
}

