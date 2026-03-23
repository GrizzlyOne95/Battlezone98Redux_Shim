
void FUN_004e54c0(int param_1,int *param_2,undefined1 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_50 [12];
  undefined8 local_44;
  float local_3c;
  undefined8 local_38;
  undefined4 local_30;
  undefined4 local_2c;
  void *local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a384;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_005fe690(param_1,0);
  local_8 = 0;
  *local_24 = GotoTask::vftable;
  local_24[0x4d] = param_2;
  *(undefined1 *)((int)local_24 + 0x13d) = param_3;
  if (param_2 == (int *)0x0) {
    uVar2 = FUN_004623e0();
    FUN_007d6c70("GotoTask: me=\"%s\" path=NULL\n",uVar2);
    puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
    local_24[0x50] = *puVar3;
    local_24[0x51] = puVar3[1];
    local_24[0x52] = puVar3[2];
    local_24[2] = 0xd;
    local_24[3] = 0xd;
    *(undefined1 *)(local_24 + 0x4f) = 0;
    local_24[0x4e] = 0;
  }
  else {
    local_24[2] = 1;
    local_24[3] = 1;
    *(undefined1 *)(local_24 + 0x4f) = 0;
    local_24[0x4e] = 0;
    if (*(int **)(param_1 + 0xb4) == param_2) {
      local_24[0x1e] = *(undefined4 *)(param_1 + 0xb0);
    }
    puVar3 = (undefined4 *)
             FUN_004e5270(local_50,*(undefined4 *)(param_2[2] + -8 + param_2[1] * 8),
                          *(undefined4 *)(param_2[2] + -4 + param_2[1] * 8),uVar1);
    local_20 = *puVar3;
    local_1c = puVar3[1];
    local_18 = puVar3[2];
    local_24[0x50] = local_20;
    local_24[0x51] = local_1c;
    local_24[0x52] = local_18;
    local_44 = CONCAT44(local_44._4_4_,(undefined4)local_44);
    local_38 = CONCAT44(local_38._4_4_,(undefined4)local_38);
    if ((param_2 != *(int **)(param_1 + 0xb4)) &&
       (local_44 = CONCAT44(local_44._4_4_,(undefined4)local_44),
       local_38 = CONCAT44(local_38._4_4_,(undefined4)local_38), *param_2 == 0)) {
      puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
      local_44 = FUN_0045c460(*puVar3,puVar3[1],puVar3[2]);
      local_38 = FUN_00444e40(*(undefined4 *)param_2[2],((undefined4 *)param_2[2])[1],local_44);
      fVar4 = (float10)FUN_00460300(local_38);
      local_3c = (float)fVar4;
      if (local_3c < 1.0) {
        local_28 = operator_new(0x18);
        local_8._0_1_ = 1;
        if (local_28 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_00460390(*param_2,param_2[1]);
        }
        local_30 = local_2c;
        local_8 = (uint)local_8._1_3_ << 8;
        local_24[0x10] = local_2c;
        memcpy(*(void **)(local_24[0x10] + 8),(void *)param_2[2],param_2[1] << 3);
      }
    }
    *(undefined1 *)((int)local_24 + 0x13e) = 0;
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

