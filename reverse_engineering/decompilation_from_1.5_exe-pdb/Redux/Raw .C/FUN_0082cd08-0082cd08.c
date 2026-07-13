
void FUN_0082cd08(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    FUN_00830222(param_1);
  }
  puVar1 = *(undefined4 **)(param_1 + 8);
  uVar2 = FUN_008309f4(param_1,param_2,param_3);
  *puVar1 = uVar2;
  puVar1[2] = 4;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  return;
}

