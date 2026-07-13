
void FUN_00508040(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  float local_44;
  float *local_40;
  float *local_3c;
  float local_38;
  float *local_34;
  float *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0082c9c5(param_1,1);
  if (iVar1 == 0) {
    iVar1 = FUN_0082c9c5(param_1,2);
    if (iVar1 == 0) {
      local_40 = (float *)FUN_004ff7c0(param_1,1);
      local_30 = (float *)FUN_004ff7c0(param_1,2);
      puVar2 = (undefined4 *)
               FUN_00440000(local_68,*local_40 / *local_30,local_40[1] / local_30[1],
                            local_40[2] / local_30[2]);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      local_18 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004ff7e0(param_1);
      *puVar2 = local_20;
      puVar2[1] = local_1c;
      puVar2[2] = local_18;
    }
    else {
      local_34 = (float *)FUN_004ff7c0(param_1,1);
      fVar3 = (float10)FUN_0082d3e1(param_1,2);
      local_38 = (float)fVar3;
      puVar2 = (undefined4 *)
               FUN_00440000(local_5c,*local_34 / local_38,local_34[1] / local_38,
                            local_34[2] / local_38);
      local_2c = *puVar2;
      local_28 = puVar2[1];
      local_24 = puVar2[2];
      puVar2 = (undefined4 *)FUN_004ff7e0(param_1);
      *puVar2 = local_2c;
      puVar2[1] = local_28;
      puVar2[2] = local_24;
    }
  }
  else {
    fVar3 = (float10)FUN_0082d3e1(param_1,1);
    local_44 = (float)fVar3;
    local_3c = (float *)FUN_004ff7c0(param_1,2);
    puVar2 = (undefined4 *)
             FUN_00440000(local_50,local_44 / *local_3c,local_44 / local_3c[1],
                          local_44 / local_3c[2]);
    local_14 = *puVar2;
    local_10 = puVar2[1];
    local_c = puVar2[2];
    puVar2 = (undefined4 *)FUN_004ff7e0(param_1);
    *puVar2 = local_14;
    puVar2[1] = local_10;
    puVar2[2] = local_c;
  }
  FUN_0083e885();
  return;
}

