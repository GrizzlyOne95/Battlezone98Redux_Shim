
void FUN_00501b00(undefined4 param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_2c [12];
  float local_20;
  float local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_004ff7a0(param_1,1);
  if (local_18 != 0) {
    fVar2 = (float10)FUN_0082c276(param_1,2,0);
    local_1c = (float)fVar2;
    fVar2 = (float10)FUN_0082c276(param_1,3,0);
    local_20 = (float)fVar2;
    puVar1 = (undefined4 *)FUN_005c9080(local_2c,local_18,local_1c,local_20);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    puVar1 = (undefined4 *)FUN_004ff7e0();
    *puVar1 = local_14;
    puVar1[1] = local_10;
    puVar1[2] = local_c;
  }
  FUN_0083e885();
  return;
}

