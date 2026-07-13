
int __thiscall FUN_00737ab0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_0071e770(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x3c);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x38);
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  return param_1;
}

