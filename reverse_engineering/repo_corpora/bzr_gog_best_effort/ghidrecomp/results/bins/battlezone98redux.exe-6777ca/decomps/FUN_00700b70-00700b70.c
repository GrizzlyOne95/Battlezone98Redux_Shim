
int __thiscall FUN_00700b70(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_006e5140(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x40) = *param_3;
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  FUN_006d4f40(param_4);
  return param_1;
}

