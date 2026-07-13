
void FUN_00504230(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_4c [12];
  int local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  float local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = FUN_004ff750(param_1,1);
  local_40 = FUN_00462630();
  if (local_40 != 0) {
    local_24 = FUN_0082ba1c(param_1,2);
    local_20 = FUN_0082c1fd(param_1,3,1);
    local_1c = FUN_004ff750(param_1,4);
    fVar3 = (float10)FUN_0082c276(param_1,6,0);
    local_2c = (float)fVar3;
    iVar1 = FUN_0082c9f5(param_1,7);
    if (iVar1 == 0) {
      local_30 = 0;
    }
    else {
      FUN_0082d377(param_1,7,0);
      local_30 = FUN_004ff060();
    }
    local_28 = local_30;
    local_34 = FUN_004ff820(param_1,5);
    if (local_34 == 0) {
      local_38 = FUN_004ff7a0(param_1,5);
      if (local_38 == 0) {
        iVar1 = FUN_0082c9f5(param_1,5);
        if (iVar1 == 0) {
          FUN_005cb790(local_18,local_24,local_20,local_1c,0,local_2c,local_28,local_28 >> 0x1f);
        }
        else {
          local_3c = FUN_0082d377(param_1,5,0);
          FUN_005cb790(local_18,local_24,local_20,local_1c,local_3c,local_2c,local_28,
                       local_28 >> 0x1f);
        }
      }
      else {
        FUN_005cb6a0(local_18,local_24,local_20,local_1c,local_38,local_2c,local_28,local_28 >> 0x1f
                    );
      }
    }
    else {
      puVar2 = (undefined4 *)FUN_00439de0(local_4c,local_34);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      FUN_005cb6a0(local_18,local_24,local_20,local_1c,&local_14,local_2c,local_28,local_28 >> 0x1f)
      ;
    }
  }
  FUN_0083e885();
  return;
}

