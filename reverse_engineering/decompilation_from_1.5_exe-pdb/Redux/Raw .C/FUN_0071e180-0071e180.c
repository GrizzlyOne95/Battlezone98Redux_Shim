
int __thiscall FUN_0071e180(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_0071e5f0(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x4c);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_2 + 0x48);
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  FUN_006d4f40(param_2 + 0x50);
  return param_1;
}

