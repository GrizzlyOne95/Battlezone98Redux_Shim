
undefined4 __fastcall FUN_00439550(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint local_10;
  uint local_c;
  int local_8;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    local_8 = param_1;
    for (local_c = 0; local_c < *(uint *)(local_8 + 0x10); local_c = local_c + 1) {
      if (*(int *)(*(int *)(local_8 + 4) + local_c * 4) != 0) {
        local_10 = 0;
        (**(code **)(**(int **)(*(int *)(local_8 + 4) + local_c * 4) + 0x24))
                  (*(undefined4 *)(*(int *)(local_8 + 4) + local_c * 4),&local_10);
        if ((local_10 & 1) == 0) break;
      }
    }
    if (local_c == *(uint *)(local_8 + 0x10)) {
      uVar2 = rand();
      uVar1 = *(undefined4 *)(*(int *)(local_8 + 4) + (uVar2 % *(uint *)(local_8 + 0x10)) * 4);
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)(local_8 + 4) + local_c * 4);
    }
  }
  return uVar1;
}

