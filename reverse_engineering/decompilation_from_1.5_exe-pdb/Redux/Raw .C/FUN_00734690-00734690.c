
int __thiscall FUN_00734690(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_0071e950(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x74);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
  *(undefined4 *)(param_1 + 0x74) = uVar1;
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_2 + 0x78);
  return param_1;
}

