
int __thiscall FUN_00733120(int param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_00733230(param_2);
  uVar1 = *(undefined4 *)(param_2 + 100);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x60);
  *(undefined4 *)(param_1 + 100) = uVar1;
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_2 + 0x68);
  return param_1;
}

