
void FUN_006cdcc0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_14 [4];
  uint local_10;
  int *local_c;
  char local_6;
  char local_5;
  
  puVar1 = (undefined4 *)FUN_0042da60();
  local_10 = FUN_00417780(*puVar1);
  local_10 = local_10 % (uint)local_c[6];
  local_5 = FUN_004221b0(local_c[5] + local_10 * 8);
  local_6 = FUN_004221b0(local_c[5] + 4 + local_10 * 8);
  if ((local_5 == '\0') || (local_6 == '\0')) {
    if (local_5 == '\0') {
      if (local_6 != '\0') {
        FUN_0044f170();
      }
    }
    else {
      FUN_0042da80();
    }
  }
  else {
    puVar1 = (undefined4 *)FID_conflict_begin(local_14);
    *(undefined4 *)(local_c[5] + 4 + local_10 * 8) = *puVar1;
    *(undefined4 *)(local_c[5] + local_10 * 8) = *(undefined4 *)(local_c[5] + 4 + local_10 * 8);
  }
  FUN_006d1900(param_1);
  *local_c = *local_c + -1;
  return;
}

