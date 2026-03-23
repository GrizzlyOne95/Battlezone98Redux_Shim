
undefined4 __thiscall FUN_004c3a00(int param_1,int *param_2)

{
  int iVar1;
  float10 fVar2;
  int local_10;
  int local_c;
  
  if ((DAT_009454ac == 0) ||
     (iVar1 = FUN_0049f100(DAT_009175a0,DAT_009175a4,param_2 + 2), iVar1 == 0)) {
    *(undefined4 *)(param_1 + 0x118) = 0;
    return 0;
  }
  local_c = -1;
  for (local_10 = 0; local_10 < param_2[1]; local_10 = local_10 + 1) {
    iVar1 = FUN_0049f100(DAT_009175a0,DAT_009175a4,*param_2 + 0x14 + local_10 * 0x24);
    if (iVar1 != 0) {
      local_c = *(int *)(*param_2 + 0xc + local_10 * 0x24);
    }
  }
  if ((((local_c != 0xd) && (local_c != 0x13)) && (local_c != 0xe)) &&
     ((local_c != 0xf && (local_c != 0x14)))) {
    *(undefined4 *)(param_1 + 0x118) = 0;
    return 0;
  }
  if (*(int *)(param_1 + 0x118) == 0) {
    *(undefined4 *)(param_1 + 0x118) = 1;
  }
  if ((DAT_00919850 == '\0') || (DAT_00919851 == '\0')) {
    if ((DAT_00919850 == '\0') && (DAT_00919851 == '\0')) {
      *(undefined4 *)(param_1 + 0x118) = 1;
    }
    else {
      if (*(int *)(param_1 + 0x118) == 1) {
        FUN_004c3780(local_c);
        *(undefined4 *)(param_1 + 0x118) = 2;
        fVar2 = (float10)FUN_00822d80();
        *(float *)(param_1 + 0x11c) = (float)fVar2;
      }
      else if ((*(int *)(param_1 + 0x118) == 2) &&
              (fVar2 = (float10)FUN_00822d80(), 1.0 < (float)fVar2 - *(float *)(param_1 + 0x11c))) {
        *(undefined4 *)(param_1 + 0x118) = 3;
      }
      if (*(int *)(param_1 + 0x118) == 3) {
        FUN_004c3780(local_c);
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(param_1 + 0x118);
  }
  FUN_004c2bd0(local_c);
  *(undefined ***)(param_1 + 0x14) = &PTR_s_edit_arw_008e81e0;
  return 1;
}

