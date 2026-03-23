
undefined4 FUN_0058c850(int param_1)

{
  bool bVar1;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x18) == -2) {
    FUN_0058c810(param_1);
  }
  else {
    bVar1 = false;
    for (local_c = *(int *)(param_1 + 0x18); local_c != -1;
        local_c = *(int *)(DAT_0091813c + local_c * 0x10)) {
      if (*(int *)(*(int *)(DAT_0091813c + 8 + local_c * 0x10) + 0x14) !=
          *(int *)(DAT_0091813c + 0xc + local_c * 0x10)) {
        bVar1 = true;
        break;
      }
    }
    if (bVar1) {
      FUN_0058c1b0(param_1);
      FUN_0058c810(param_1);
    }
  }
  return *(undefined4 *)(param_1 + 0x18);
}

