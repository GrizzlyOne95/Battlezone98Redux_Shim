
void FUN_0082cdd2(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)FUN_0082c4a6(param_1,param_2);
  puVar1 = *(undefined4 **)(param_1 + 8);
  *puVar1 = *puVar2;
  puVar1[1] = puVar2[1];
  puVar1[2] = puVar2[2];
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

