
void FUN_0082cbf5(int param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = *(uint **)(param_1 + 8);
  *puVar1 = (uint)(param_2 != 0);
  puVar1[2] = 1;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

