
void FUN_00507cd0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_28 [12];
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = (undefined4 *)FUN_004ff7c0(param_1,1);
  local_1c = (undefined4 *)FUN_004ff7c0(param_1,2);
  puVar1 = (undefined4 *)
           FUN_00440130(local_28,*local_18,local_18[1],local_18[2],*local_1c,local_1c[1],local_1c[2]
                       );
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  puVar1 = (undefined4 *)FUN_004ff7e0(param_1);
  *puVar1 = local_14;
  puVar1[1] = local_10;
  puVar1[2] = local_c;
  FUN_0083e885();
  return;
}

