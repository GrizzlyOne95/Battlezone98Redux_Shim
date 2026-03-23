
void FUN_00695740(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      FUN_0069d940(*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4));
    }
  }
  return;
}

