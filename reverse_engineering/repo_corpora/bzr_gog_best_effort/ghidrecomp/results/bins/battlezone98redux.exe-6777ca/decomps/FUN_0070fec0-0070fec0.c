
int __thiscall FUN_0070fec0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_00700b10(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x34);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x38);
  return param_1;
}

