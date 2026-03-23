
undefined4 * FUN_00460390(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 local_10;
  int local_c;
  undefined4 *local_8;
  
  FUN_00430590();
  *local_8 = 0;
  FUN_00460de0(param_1);
  local_8[1] = param_2;
  local_10 = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)local_8[1] * 8 >> 0x20) != 0) |
                          (uint)((ulonglong)(uint)local_8[1] * 8));
  local_8[2] = local_10;
  for (local_c = 0; local_c < (int)local_8[1]; local_c = local_c + 1) {
    *(undefined4 *)(local_8[2] + local_c * 8) = 0;
    *(undefined4 *)(local_8[2] + 4 + local_c * 8) = 0;
  }
  local_14 = local_8;
  puVar1 = (undefined4 *)FID_conflict_begin(local_1c);
  local_18 = *puVar1;
  puVar1 = (undefined4 *)FUN_004613b0(local_20,local_18,&local_14);
  local_8[5] = *puVar1;
  *(undefined1 *)(local_8 + 3) = 0;
  local_8[4] = 0;
  return local_8;
}

