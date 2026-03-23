
void FUN_00444690(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 *param_7,undefined4 param_8,
                 float param_9,float *param_10,undefined4 *param_11)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_7;
  fVar3 = (float10)FUN_004428b0(param_7,&param_1);
  local_28 = (float)fVar3;
  local_24 = local_28 + (float)param_7[3];
  if (-0.1 < local_24) {
    fVar3 = (float10)FUN_004428b0(local_18,&param_4);
    local_20 = (float)fVar3;
    if ((local_20 < -1.1920929e-07) && (local_1c = -local_24 / local_20, local_1c <= param_9)) {
      puVar1 = (undefined4 *)
               FUN_00439d00(local_34,param_1,param_2,param_3,local_1c,param_4,param_5,param_6);
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      iVar2 = FUN_004447e0(param_7,param_8,&local_14);
      if (iVar2 != 0) {
        *param_10 = local_1c;
        *param_11 = *local_18;
        param_11[1] = local_18[1];
        param_11[2] = local_18[2];
      }
    }
  }
  FUN_0083e885();
  return;
}

