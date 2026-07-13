
void FUN_004a7520(undefined4 *param_1,uint param_2,uint param_3,uint param_4)

{
  undefined4 *puVar1;
  undefined1 local_20 [12];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)
           FUN_00440000(local_20,param_2 ^ 0x80000000,param_3 ^ 0x80000000,param_4 ^ 0x80000000);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  FUN_0083e885();
  return;
}

