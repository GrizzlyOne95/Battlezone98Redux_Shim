
int __thiscall FUN_006f2280(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_006e5cd0(param_2);
  uVar1 = *(undefined4 *)(param_2 + 0x6c);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x68);
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  return param_1;
}

