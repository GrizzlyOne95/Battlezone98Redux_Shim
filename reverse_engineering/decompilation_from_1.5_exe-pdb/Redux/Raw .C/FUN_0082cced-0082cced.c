
void FUN_0082cced(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  *puVar1 = param_2;
  puVar1[2] = 2;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

