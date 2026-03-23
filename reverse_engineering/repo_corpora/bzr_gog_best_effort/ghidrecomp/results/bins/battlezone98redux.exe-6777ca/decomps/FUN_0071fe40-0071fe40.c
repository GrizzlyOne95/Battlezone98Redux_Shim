
int __thiscall FUN_0071fe40(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  
  FUN_007129b0(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x60) = *param_3;
  *(undefined4 *)(param_1 + 100) = uVar1;
  *(undefined4 *)(param_1 + 0x68) = *param_4;
  return param_1;
}

