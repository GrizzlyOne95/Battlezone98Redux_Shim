
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a7900(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x413;
      FUN_006a5f50(0x800,"SCHEDULER: MATCHING RESOURCES.",0);
    }
    FUN_006a7440();
    iVar2 = FUN_006a7680();
    if (iVar2 != 0) {
      *(undefined4 *)(param_1 + 0x14) = 1;
      FUN_006a78c0();
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

