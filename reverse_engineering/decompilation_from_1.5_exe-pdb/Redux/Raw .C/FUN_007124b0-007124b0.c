
int __thiscall
FUN_007124b0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  
  FUN_00447eb0(param_4);
  *(undefined4 *)(param_1 + 4) = param_2;
  uVar1 = param_3[1];
  *(undefined4 *)(param_1 + 8) = *param_3;
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  <>(param_5);
  return param_1;
}

