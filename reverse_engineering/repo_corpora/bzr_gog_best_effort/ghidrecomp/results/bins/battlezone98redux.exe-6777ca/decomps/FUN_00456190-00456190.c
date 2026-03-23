
void FUN_00456190(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 local_24 [12];
  undefined4 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00448f10(param_1,param_2,param_3);
  *local_18 = TracerRender::vftable;
  puVar1 = (undefined4 *)FUN_00439de0(local_24,param_3);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  local_18[0x1c] = local_14;
  local_18[0x1d] = local_10;
  local_18[0x1e] = local_c;
  local_18[0x1f] = 0;
  FUN_0083e885();
  return;
}

