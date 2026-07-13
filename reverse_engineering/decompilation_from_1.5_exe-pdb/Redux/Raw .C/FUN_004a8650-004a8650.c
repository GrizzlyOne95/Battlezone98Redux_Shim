
void __thiscall FUN_004a8650(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  float fVar2;
  float10 fVar3;
  undefined1 local_4c [12];
  undefined8 local_40;
  float local_38;
  undefined8 local_34;
  undefined8 local_2c;
  float local_24;
  undefined8 local_20;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  puVar1 = (undefined4 *)FUN_004560b0(local_4c,*(int *)(param_1 + 0xf4) + 0x20);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  local_2c = FUN_0045c460(local_14,local_10,local_c);
  local_20 = local_2c;
  local_40 = FUN_004622a0(local_2c);
  local_20 = local_40;
  local_34 = FUN_004622a0(param_2,param_3);
  fVar2 = (float)((ulonglong)local_34 >> 0x20);
  local_38 = (float)local_20 * (float)local_34 + local_20._4_4_ * fVar2;
  local_24 = (float)local_20 * fVar2 - local_20._4_4_ * (float)local_34;
  if (local_38 <= 0.0) {
    if (0.0 <= local_24) {
      *(undefined4 *)(*(int *)(local_18 + 0x230) + 0xc4) = 0x3f800000;
    }
    else {
      *(undefined4 *)(*(int *)(local_18 + 0x230) + 0xc4) = 0xbf800000;
    }
  }
  else {
    fVar3 = (float10)FUN_00447ed0(local_24 * 3.0 - *(float *)(local_18 + 0x13c) * 0.5,0xbf800000,
                                  0x3f800000);
    *(float *)(*(int *)(local_18 + 0x230) + 0xc4) = (float)fVar3;
  }
  FUN_0083e885();
  return;
}

