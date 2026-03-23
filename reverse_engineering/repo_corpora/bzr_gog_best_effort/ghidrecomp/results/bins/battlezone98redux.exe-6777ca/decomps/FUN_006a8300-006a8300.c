
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a8300(int param_1)

{
  int iVar1;
  
  if (((*(int *)(*(int *)(param_1 + 0x40) + 4) != 0) && (iVar1 = FUN_006a6910(), iVar1 != 1)) &&
     (iVar1 = FUN_006a6bf0(), iVar1 != 1)) {
    FUN_006a6da0();
    iVar1 = FUN_006a70b0();
    if (*(int *)(param_1 + 0x24) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 1;
      *(undefined4 *)(param_1 + 0x14) = 1;
    }
    if (((iVar1 != 1) && (iVar1 = FUN_006a7180(), iVar1 != 1)) &&
       ((iVar1 = FUN_006a7900(), iVar1 != 1 && (iVar1 = FUN_006a79a0(), iVar1 != 1)))) {
      FUN_006a7f10();
      if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
         (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\scheduler.cpp";
        _DAT_009310c0 = 0x65a;
        FUN_006a5f50(0x800,"ALL DONE ALL DONE ALL DONE\n\n");
      }
      FUN_006a7c80();
    }
  }
  return;
}

