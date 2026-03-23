
void FUN_00691860(int param_1,int param_2)

{
  int *piVar1;
  int local_10;
  int local_8;
  
  piVar1 = *(int **)(*(int *)(param_1 + 0xb4) + param_2 * 4);
  if (piVar1 != (int *)0x0) {
    local_8 = 0;
    do {
      switch(*(undefined4 *)(piVar1[1] + 4 + local_8 * 0x10)) {
      case 0:
        local_10 = FUN_006912b0(param_1,local_8 * 0x10 + piVar1[1],param_2);
        break;
      case 1:
        local_10 = FUN_00691390(param_1,local_8 * 0x10 + piVar1[1],param_2);
        break;
      case 2:
        local_10 = FUN_00691660(param_1,local_8 * 0x10 + piVar1[1],param_2);
        break;
      case 3:
        local_10 = FUN_00691450(param_1,local_8 * 0x10 + piVar1[1],param_2);
        break;
      default:
        FUN_006a5f50(1,
                     "Error in ai construction account #%d, priority level #%d illegal build type is %d\n"
                     ,param_2,local_8,*(undefined4 *)(piVar1[1] + 4 + local_8 * 0x10));
        local_10 = 0;
      }
      local_8 = local_8 + 1;
    } while ((local_10 == 0) && (local_8 < *piVar1));
  }
  return;
}

