
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a6bf0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int local_10;
  
  if (*(int *)(param_1 + 4) == 0) {
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x10d;
      FUN_006a5f50(0x800,"Preparing all squads for scheduling");
    }
    for (local_10 = 0; local_10 < *(int *)(*(int *)(param_1 + 0x40) + 0x24); local_10 = local_10 + 1
        ) {
      puVar2 = (undefined4 *)FUN_0069d590(*(int *)(param_1 + 0x40) + 0x1c,local_10);
      FUN_006a8a30(puVar2);
      puVar2[8] = 0;
      puVar2[9] = puVar2[5];
      puVar2[0xe] = 0;
      puVar2[0xf] = 0;
      if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
         (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
        if (puVar2[10] == 0) {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x131;
          FUN_006a5f50(0x800,"SQUAD %d...(%d, %d).....U: %d    Str: %d  --------",*puVar2,puVar2[1],
                       puVar2[2],puVar2[5],puVar2[0xd]);
        }
        else {
          _DAT_009310bc = "Schedule\\scheduler.cpp";
          _DAT_009310c0 = 0x143;
          FUN_006a5f50(0x800,"SQUAD %d (%d, %d)........U: %d    Str: %d  ",*puVar2,puVar2[1],
                       puVar2[2],puVar2[5],puVar2[0xd]);
        }
      }
    }
    *(undefined4 *)(param_1 + 4) = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

