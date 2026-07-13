
void __fastcall FUN_0077bc30(int param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  
  *(undefined1 *)(param_1 + 0x85) = 0;
  if (*(int *)(param_1 + 0x44) != 0) {
    for (local_c = 0; local_c < (int)*(float *)(param_1 + 0x48); local_c = local_c + 1) {
      for (local_10 = 0; local_10 < (int)*(float *)(param_1 + 0x4c); local_10 = local_10 + 1) {
        iVar1 = (int)*(float *)(param_1 + 0x4c) * local_c + local_10;
        if (*(int *)(*(int *)(param_1 + 0x44) + iVar1 * 4) != 0) {
          FUN_0077bd10(1);
        }
        *(undefined4 *)(*(int *)(param_1 + 0x44) + iVar1 * 4) = 0;
      }
    }
    free(*(void **)(param_1 + 0x44));
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  return;
}

