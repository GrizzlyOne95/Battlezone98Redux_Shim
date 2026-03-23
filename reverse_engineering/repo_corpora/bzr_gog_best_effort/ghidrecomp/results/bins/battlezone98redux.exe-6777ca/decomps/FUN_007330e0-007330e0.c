
int __thiscall FUN_007330e0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_007331a0(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x6c);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x68);
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
  return param_1;
}

