
undefined4 FUN_004e3510(int param_1)

{
  int iVar1;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x68); local_8 = local_8 + 1) {
    iVar1 = local_8 * 0x10 + *(int *)(param_1 + 0x74);
    if (*(int *)(iVar1 + 4) != 0) {
      FUN_004e3990(*(undefined4 *)(iVar1 + 4));
    }
  }
  free(*(void **)(param_1 + 0x74));
  *(int *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  return 1;
}

