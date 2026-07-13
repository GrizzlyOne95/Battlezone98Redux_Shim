
undefined4 FUN_006a8630(int *param_1,undefined4 param_2,double param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1[2] < param_1[3]) {
    local_c = 0;
    local_10 = param_1[2] + -1;
    while (-1 < local_10 - local_c) {
      iVar2 = (local_10 + local_c) / 2;
      if (*(double *)(param_1[1] + iVar2 * 8) <= param_3) {
        local_c = iVar2 + 1;
      }
      else {
        local_10 = iVar2 + -1;
      }
    }
    for (local_8 = param_1[2]; local_c < local_8; local_8 = local_8 + -1) {
      *(undefined4 *)(*param_1 + local_8 * 4) = *(undefined4 *)(*param_1 + -4 + local_8 * 4);
    }
    for (local_8 = param_1[2]; local_c < local_8; local_8 = local_8 + -1) {
      *(undefined8 *)(param_1[1] + local_8 * 8) = *(undefined8 *)(param_1[1] + -8 + local_8 * 8);
    }
    *(double *)(param_1[1] + local_c * 8) = param_3;
    *(undefined4 *)(*param_1 + local_c * 4) = param_2;
    param_1[2] = param_1[2] + 1;
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

