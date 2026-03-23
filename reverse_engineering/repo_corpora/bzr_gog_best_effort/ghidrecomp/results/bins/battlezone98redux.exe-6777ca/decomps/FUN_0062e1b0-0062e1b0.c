
void FUN_0062e1b0(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined1 local_20 [12];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00439de0(local_20,param_2 + 0x20);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  for (param_2 = *(int *)(param_2 + 0x78); (param_2 != 0 && (param_2 != param_3));
      param_2 = *(int *)(param_2 + 0x78)) {
    FUN_00820180(&local_14,&local_14,1,param_2 + 0x20);
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  FUN_0083e885();
  return;
}

