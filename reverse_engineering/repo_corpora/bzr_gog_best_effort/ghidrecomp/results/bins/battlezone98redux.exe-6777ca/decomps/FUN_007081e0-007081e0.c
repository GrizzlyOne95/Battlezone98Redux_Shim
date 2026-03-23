
int __thiscall FUN_007081e0(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  FUN_006e51f0(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x38) = *param_3;
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  return param_1;
}

