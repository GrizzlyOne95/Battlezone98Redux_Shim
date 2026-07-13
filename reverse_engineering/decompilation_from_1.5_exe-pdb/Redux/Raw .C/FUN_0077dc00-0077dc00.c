
void FUN_0077dc00(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  float10 fVar3;
  undefined1 local_2c [12];
  double local_20;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_0077d7c0(local_2c,param_1,param_2);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  fVar3 = (float10)FUN_004428b0(&local_14,&DAT_02ceb830);
  local_20 = (double)fVar3;
  if (0.00390625 <= local_20) {
    if (local_20 <= 0.99609375) {
      local_18 = (int)(local_20 * 256.0);
    }
    else {
      local_18 = 0xff;
    }
  }
  else {
    local_18 = 0;
  }
  puVar2 = (undefined1 *)FUN_0050ce30(param_1,param_2);
  *puVar2 = (undefined1)local_18;
  FUN_0083e885();
  return;
}

