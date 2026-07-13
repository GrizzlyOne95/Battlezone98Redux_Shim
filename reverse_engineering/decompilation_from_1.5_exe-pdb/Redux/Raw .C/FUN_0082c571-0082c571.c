
undefined4 FUN_0082c571(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x58);
  *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x58) = param_2;
  return uVar1;
}

