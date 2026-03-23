
undefined4 __thiscall FUN_004c2770(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  iVar1 = FUN_0049f100(DAT_009175a0,DAT_009175a4,param_2 + 2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (DAT_00919850 == '\0') {
      *(undefined4 *)(param_1 + 0x18) = 0;
    }
    else {
      if (*(int *)(param_1 + 0x18) == 0) {
        for (local_c = 0; local_c < param_2[1]; local_c = local_c + 1) {
          iVar1 = FUN_0049f100(DAT_009175a0,DAT_009175a4,*param_2 + 0x14 + local_c * 0x24);
          if (iVar1 != 0) {
            param_2[6] = local_c;
            break;
          }
        }
      }
      *(undefined4 *)(param_1 + 0x18) = 1;
    }
    if (DAT_00919851 == '\0') {
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    *(undefined ***)(param_1 + 0x14) = &PTR_s_edit_arw_008e81e0;
    uVar2 = 1;
  }
  return uVar2;
}

