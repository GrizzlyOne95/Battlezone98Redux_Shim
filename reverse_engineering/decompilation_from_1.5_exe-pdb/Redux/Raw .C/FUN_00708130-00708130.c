
int __thiscall FUN_00708130(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_006f6120(param_2);
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 0x48) = *param_3;
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  FUN_006d4f40(param_4);
  return param_1;
}

