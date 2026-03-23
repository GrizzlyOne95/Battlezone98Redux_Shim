
void FUN_00694ed0(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      FUN_00694f90(0);
    }
  }
  free(*(void **)**(undefined4 **)(param_1 + 0x80));
  FUN_0069f010(*(undefined4 *)(param_1 + 0x80),0,*(undefined4 *)(param_1 + 0x78),0,
               *(undefined4 *)(param_1 + 0x7c));
  return;
}

