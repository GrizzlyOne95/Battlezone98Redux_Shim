
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a67b0(int param_1)

{
  int iVar1;
  int local_c;
  
  if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
     (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
    _DAT_009310bc = "Schedule\\scheduler.cpp";
    _DAT_009310c0 = 0x2e;
    FUN_006a5f50(0x800,"Subschedule CLEAN-UP");
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    FUN_0069d280(*(undefined4 *)(param_1 + 0x28));
    for (local_c = 0; local_c < *(int *)(*(int *)(param_1 + 0x24) + 8); local_c = local_c + 1) {
      iVar1 = FUN_006a8750(*(undefined4 *)(param_1 + 0x24),local_c);
      if (*(int *)(iVar1 + 0x20) == 0) {
        FUN_006a88c0(iVar1);
      }
    }
    FUN_006a85f0(*(undefined4 *)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  return;
}

