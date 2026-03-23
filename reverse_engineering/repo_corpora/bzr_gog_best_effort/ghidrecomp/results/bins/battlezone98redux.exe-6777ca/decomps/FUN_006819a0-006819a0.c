
bool FUN_006819a0(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  bool bVar2;
  
  bVar2 = *(int *)(param_1 + 0xac) != 0;
  if (bVar2) {
    puVar1 = (undefined4 *)(**(code **)(**(int **)(param_1 + 0xac) + 0x34))();
    *param_2 = *puVar1;
    param_2[1] = puVar1[1];
    param_2[2] = puVar1[2];
  }
  return bVar2;
}

