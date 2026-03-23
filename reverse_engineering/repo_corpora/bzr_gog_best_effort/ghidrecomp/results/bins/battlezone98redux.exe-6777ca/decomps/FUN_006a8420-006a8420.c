
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006a8420(int param_1)

{
  undefined4 *puVar1;
  int local_10;
  
  FUN_006a8760(*(int *)(param_1 + 0x40) + 0x1c,"Schedule\\scheduler.cpp",0x66c);
  local_10 = *(int *)(*(int *)(param_1 + 0x40) + 0x24);
  while (local_10 = local_10 + -1, -1 < local_10) {
    puVar1 = (undefined4 *)FUN_0069d590(*(int *)(param_1 + 0x40) + 0x1c,local_10);
    if ((puVar1 != (undefined4 *)0x0) && (puVar1[10] != 0)) {
      (**(code **)(*(int *)puVar1[10] + 0x28))();
    }
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x68c;
      FUN_006a5f50(0x800,"Sending group %d",*puVar1);
    }
  }
  FUN_006a8760(*(int *)(param_1 + 0x40) + 0x1c,"Schedule\\scheduler.cpp",0x694);
  *(undefined4 *)(param_1 + 0x98) = 1;
  return;
}

