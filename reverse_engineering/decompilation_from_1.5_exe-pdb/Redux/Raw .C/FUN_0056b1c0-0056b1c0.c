
void FUN_0056b1c0(undefined4 *param_1,undefined4 *param_2,int param_3,byte param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_38 [12];
  float local_2c;
  undefined1 local_21;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = (uint)param_4;
  uVar2 = (**(code **)(*(int *)(param_3 + 0x18) + 0xc))(uVar1);
  local_21 = FUN_0056b160(param_1,param_2,uVar2,uVar1);
  if (param_4 != 0) {
    fVar4 = (float10)FUN_00417910(*param_2);
    local_2c = (float)fVar4;
    puVar3 = (undefined4 *)FUN_004624b0();
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    puVar3 = (undefined4 *)FUN_004624b0();
    fVar4 = (float10)FUN_00417910(*param_2,*puVar3,puVar3[1],puVar3[2]);
    puVar3 = (undefined4 *)FUN_00439d00(local_38,*param_1,param_1[1],param_1[2],(float)fVar4);
    local_14 = *puVar3;
    local_10 = puVar3[1];
    local_c = puVar3[2];
    *param_1 = local_14;
    param_1[1] = local_10;
    param_1[2] = local_c;
  }
  FUN_0083e885();
  return;
}

