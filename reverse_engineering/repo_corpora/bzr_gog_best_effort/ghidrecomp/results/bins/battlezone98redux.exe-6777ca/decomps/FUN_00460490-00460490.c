
undefined4 * FUN_00460490(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 *local_10;
  undefined4 local_c;
  undefined4 *local_8;
  
  FUN_00430590();
  *local_8 = 0;
  local_8[1] = 2;
  local_c = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)local_8[1] * 8 >> 0x20) != 0) |
                         (uint)((ulonglong)(uint)local_8[1] * 8));
  local_8[2] = local_c;
  *(undefined4 *)local_8[2] = *param_1;
  *(undefined4 *)(local_8[2] + 4) = param_1[2];
  *(undefined4 *)(local_8[2] + 8) = *param_2;
  *(undefined4 *)(local_8[2] + 0xc) = param_2[2];
  local_10 = local_8;
  puVar1 = (undefined4 *)FID_conflict_begin(local_18);
  local_14 = *puVar1;
  puVar1 = (undefined4 *)FUN_004613b0(local_1c,local_14,&local_10);
  local_8[5] = *puVar1;
  *(undefined1 *)(local_8 + 3) = 0;
  local_8[4] = 0;
  return local_8;
}

