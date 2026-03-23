
void __thiscall FUN_005929e0(int param_1,undefined4 param_2,undefined4 param_3)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int local_c;
  
  if (*(int *)(param_1 + 4) < *(int *)(param_1 + 8) + -1) {
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    *(undefined4 *)(*(int *)(param_1 + 0x10) + *(int *)(param_1 + 4) * 8) = param_3;
    *(undefined4 *)(*(int *)(param_1 + 0x10) + 4 + *(int *)(param_1 + 4) * 8) = param_2;
    fVar1 = *(float *)(*(int *)(param_1 + 0x10) + *(int *)(param_1 + 4) * 8);
    uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4 + *(int *)(param_1 + 4) * 8);
    local_c = *(int *)(param_1 + 4);
    while ((0 < local_c &&
           (iVar5 = local_c >> 1, *(float *)(*(int *)(param_1 + 0x10) + iVar5 * 8) <= fVar1))) {
      uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4 + iVar5 * 8);
      iVar4 = *(int *)(param_1 + 0x10);
      *(undefined4 *)(iVar4 + local_c * 8) = *(undefined4 *)(*(int *)(param_1 + 0x10) + iVar5 * 8);
      *(undefined4 *)(iVar4 + 4 + local_c * 8) = uVar3;
      local_c = iVar5;
    }
    iVar5 = *(int *)(param_1 + 0x10);
    *(float *)(iVar5 + local_c * 8) = fVar1;
    *(undefined4 *)(iVar5 + 4 + local_c * 8) = uVar2;
    return;
  }
  if (DAT_02cc2bd8 == '\0') {
    DAT_02cc2bd8 = '\x01';
    FUN_0081e0c0("Uhoh, too many items in Heap_Class! (max = %d)\n",*(undefined4 *)(param_1 + 8));
  }
                    /* WARNING: Subroutine does not return */
  exit(1);
}

