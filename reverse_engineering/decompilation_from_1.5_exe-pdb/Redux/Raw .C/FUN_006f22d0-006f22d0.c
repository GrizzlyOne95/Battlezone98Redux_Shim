
int __thiscall FUN_006f22d0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_006e5d70(param_2);
  uVar1 = *(undefined4 *)(param_2 + 100);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
  *(undefined4 *)(param_1 + 100) = uVar1;
  return param_1;
}

