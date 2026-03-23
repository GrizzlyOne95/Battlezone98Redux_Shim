
void FUN_005c8bd0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_2c [12];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_005c8220(&local_20,param_2,param_3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_00440000(local_2c,0,0,0);
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  else {
    *param_1 = local_20;
    param_1[1] = local_1c;
    param_1[2] = local_18;
  }
  FUN_0083e885();
  return;
}

