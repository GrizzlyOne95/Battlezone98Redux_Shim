
int * FUN_005a7d00(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int *local_c;
  
  local_c = (int *)FUN_004e0f70(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  if (local_c == (int *)0x0) {
    local_c = &DAT_025cd000;
  }
  piVar1 = (int *)(**(code **)(*local_c + 4))(param_1);
  *(int **)(piVar1[0x8a] + 0x120) = piVar1;
  uVar2 = FUN_0047e9a0(param_1);
  (**(code **)(*piVar1 + 4))(uVar2);
  return piVar1;
}

