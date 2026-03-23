
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a6880(int param_1)

{
  if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
     (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
    _DAT_009310bc = "Schedule\\scheduler.cpp";
    _DAT_009310c0 = 0x5c;
    FUN_006a5f50(0x800,"RESET SUBSCHEDULE******************");
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  FUN_006a67b0();
  return;
}

