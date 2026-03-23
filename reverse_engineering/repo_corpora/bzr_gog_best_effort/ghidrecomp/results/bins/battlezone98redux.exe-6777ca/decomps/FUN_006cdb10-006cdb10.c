
undefined4 __thiscall FUN_006cdb10(int *param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  int *local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  local_c = param_1;
  if ((uint)param_1[6] <= *param_1 + 1U) {
    uVar2 = FUN_006d15a0(*param_1 + 1);
    FUN_006d1600(uVar2);
  }
  local_10 = FUN_00417780(*param_3);
  local_10 = local_10 % (uint)local_c[6];
  local_14 = *(undefined4 *)(local_c[5] + local_10 * 8);
  uVar2 = FID_conflict_begin(local_1c);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    local_18 = *(undefined4 *)(local_c[5] + 4 + local_10 * 8);
    FUN_0042da80();
    while (cVar1 = FUN_00420f10(&local_18), cVar1 != '\0') {
      piVar4 = (int *)FUN_0042da60();
      if (*piVar4 == *param_3) {
        local_6 = 0;
        FUN_0042c980(&local_14,&local_6);
        return param_2;
      }
      FUN_0042da80();
    }
    puVar3 = (undefined4 *)FUN_006d1850(local_28,local_18,param_3);
    *(undefined4 *)(local_c[5] + 4 + local_10 * 8) = *puVar3;
    *local_c = *local_c + 1;
    local_7 = 1;
    FUN_0042c980(local_c[5] + 4 + local_10 * 8,&local_7);
  }
  else {
    puVar3 = (undefined4 *)FID_conflict_begin(local_20);
    puVar3 = (undefined4 *)FUN_006d1850(local_24,*puVar3,param_3);
    *(undefined4 *)(local_c[5] + 4 + local_10 * 8) = *puVar3;
    *(undefined4 *)(local_c[5] + local_10 * 8) = *(undefined4 *)(local_c[5] + 4 + local_10 * 8);
    *local_c = *local_c + 1;
    local_5 = 1;
    FUN_0042c980(local_c[5] + 4 + local_10 * 8,&local_5);
  }
  return param_2;
}

