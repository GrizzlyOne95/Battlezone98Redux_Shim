
int __thiscall FUN_006ff7b0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_006e69c0(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x44);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  FUN_006d4f40(param_2 + 0x48);
  return param_1;
}

