
int __thiscall FUN_00735e10(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_007270d0(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x5c);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
  return param_1;
}

