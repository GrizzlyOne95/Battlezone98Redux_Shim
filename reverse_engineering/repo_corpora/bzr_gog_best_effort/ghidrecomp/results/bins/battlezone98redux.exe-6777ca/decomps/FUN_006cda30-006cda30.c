
undefined4 * __thiscall FUN_006cda30(int param_1,undefined4 *param_2,int *param_3)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_18 [4];
  undefined4 local_14;
  uint local_10;
  undefined4 local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x18) != 0) {
    local_10 = FUN_00417780(*param_3);
    local_10 = local_10 % *(uint *)(local_8 + 0x18);
    local_c = *(undefined4 *)(*(int *)(local_8 + 0x14) + local_10 * 8);
    uVar2 = FID_conflict_begin(local_18);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 != '\0') {
      FID_conflict_begin(param_2);
      return param_2;
    }
    local_14 = *(undefined4 *)(*(int *)(local_8 + 0x14) + 4 + local_10 * 8);
    FUN_0042da80();
    while (cVar1 = FUN_00420f10(&local_14), cVar1 != '\0') {
      piVar3 = (int *)FUN_0042da60();
      if (*piVar3 == *param_3) {
        *param_2 = local_c;
        return param_2;
      }
      FUN_0042da80();
    }
  }
  FID_conflict_begin(param_2);
  return param_2;
}

