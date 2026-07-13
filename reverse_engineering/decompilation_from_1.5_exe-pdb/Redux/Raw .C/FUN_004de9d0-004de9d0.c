
void FUN_004de9d0(undefined4 param_1,undefined4 *param_2,float *param_3)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_24 [12];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_00479f30(param_1);
  if (local_18 == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_24,0,0,0);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    *param_2 = local_14;
    param_2[1] = local_10;
    param_2[2] = local_c;
    *param_3 = 0.0;
  }
  else {
    puVar1 = (undefined4 *)FUN_004624b0();
    *param_2 = *puVar1;
    param_2[1] = puVar1[1];
    param_2[2] = puVar1[2];
    fVar2 = (float10)FUN_004624d0();
    *param_3 = (float)fVar2;
  }
  FUN_0083e885();
  return;
}

