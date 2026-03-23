
void FUN_0082f76f(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  *(undefined4 **)(param_1 + 0x14) = *(undefined4 **)(param_1 + 0x28);
  uVar1 = **(undefined4 **)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  FUN_0082f92f(param_1,uVar1);
  FUN_0082f5f3(param_1,param_2,*(undefined4 *)(param_1 + 0xc));
  *(undefined2 *)(param_1 + 0x34) = *(undefined2 *)(param_1 + 0x36);
  *(undefined1 *)(param_1 + 0x39) = 1;
  FUN_0082f7b4(param_1);
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}

