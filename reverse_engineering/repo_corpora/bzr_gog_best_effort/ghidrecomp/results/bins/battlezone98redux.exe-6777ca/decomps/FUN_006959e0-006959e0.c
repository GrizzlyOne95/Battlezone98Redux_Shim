
void FUN_006959e0(int param_1)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4);
      *(int *)(iVar1 + 0x48) = *(int *)(*(int *)(param_1 + 0x60) + 4) * *(int *)(iVar1 + 0x50);
      if (*(int *)(param_1 + 100) < *(int *)(iVar1 + 0x48)) {
        *(undefined4 *)(param_1 + 100) = *(undefined4 *)(iVar1 + 0x48);
      }
    }
  }
  return;
}

