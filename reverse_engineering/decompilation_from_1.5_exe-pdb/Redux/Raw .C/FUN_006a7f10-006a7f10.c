
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a7f10(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int local_c;
  
  if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
     (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
    _DAT_009310bc = "Schedule\\scheduler.cpp";
    _DAT_009310c0 = 0x561;
    FUN_006a5f50(0x800,"Scheduler CLEAN-UP");
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    FUN_006a85f0(*(undefined4 *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    FUN_0069d310(*(undefined4 *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    for (local_c = 0; local_c < *(int *)(*(int *)(param_1 + 0x24) + 8); local_c = local_c + 1) {
      iVar1 = FUN_006a8750(*(undefined4 *)(param_1 + 0x24),local_c);
      if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
         (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\scheduler.cpp";
        _DAT_009310c0 = 0x586;
        FUN_006a5f50(0x800,"The Match Contains @%d\n",iVar1);
      }
      if (*(int *)(iVar1 + 0x20) == 0) {
        FUN_006a88c0(iVar1);
      }
    }
    FUN_006a85f0(*(undefined4 *)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    for (local_c = 0; local_c < *(int *)(*(int *)(param_1 + 0x2c) + 8); local_c = local_c + 1) {
      puVar2 = (undefined4 *)FUN_0069d590(*(undefined4 *)(param_1 + 0x2c),local_c);
      if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
         (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\scheduler.cpp";
        _DAT_009310c0 = 0x5a7;
        FUN_006a5f50(0x800,"GOOD Match Contains @%d\n",puVar2);
      }
      if (puVar2 == (undefined4 *)0x0) {
        if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
           (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x5c6;
          FUN_006a5f50(0x800,"Good Matches list contains NULL match");
        }
      }
      else {
        if (*(int *)(param_1 + 0x18) == 0) {
          FUN_006a8900(*puVar2);
          *puVar2 = 0;
        }
        FUN_006a88c0(puVar2);
      }
    }
    FUN_0069d310(*(undefined4 *)(param_1 + 0x2c));
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    for (local_c = 0; local_c < *(int *)(*(int *)(param_1 + 0x34) + 8); local_c = local_c + 1) {
      iVar1 = FUN_0069d590(*(undefined4 *)(param_1 + 0x34),local_c);
      if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
         (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\scheduler.cpp";
        _DAT_009310c0 = 0x5e0;
        FUN_006a5f50(0x800,"Deleting goal @%d\n",iVar1);
      }
      if (iVar1 == 0) {
        if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
           (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x5fb;
          FUN_006a5f50(0x800,"the_goal list contains NULL goal");
        }
      }
      else {
        if (*(int *)(iVar1 + 0x14) != 0) {
          FUN_006a89e0(*(undefined4 *)(iVar1 + 0x14));
        }
        if (iVar1 != 0) {
          FUN_006a82d0(1);
        }
      }
    }
    FUN_0069d280(*(undefined4 *)(param_1 + 0x34));
  }
  *(undefined4 *)(param_1 + 0x9c) = 1;
  return;
}

