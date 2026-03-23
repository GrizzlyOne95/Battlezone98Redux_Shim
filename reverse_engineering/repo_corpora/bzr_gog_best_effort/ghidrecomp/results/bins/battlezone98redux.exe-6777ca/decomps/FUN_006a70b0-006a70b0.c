
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a70b0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x227;
      FUN_006a5f50(0x800,"Initializing the match lists");
    }
    iVar2 = *(int *)(*(int *)(param_1 + 0x40) + 0x24) * *(int *)(*(int *)(param_1 + 0x28) + 8);
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x24) = 0;
      *(undefined4 *)(param_1 + 0x10) = 1;
      uVar1 = 1;
    }
    else {
      uVar1 = FUN_006a8590(iVar2);
      *(undefined4 *)(param_1 + 0x24) = uVar1;
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x10) = 1;
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

