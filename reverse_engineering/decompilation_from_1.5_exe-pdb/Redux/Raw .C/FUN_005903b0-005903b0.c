
void FUN_005903b0(float *param_1,float *param_2)

{
  float fVar1;
  char cVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined8 uVar5;
  undefined1 local_13c [24];
  undefined1 local_124 [60];
  undefined4 local_e8;
  undefined8 local_e4;
  float local_dc;
  int local_d8;
  undefined8 local_d4;
  float local_cc;
  int local_c8;
  float local_c4;
  float local_c0;
  int local_bc;
  float local_b8;
  int local_b4;
  int local_b0;
  float *local_ac;
  float *local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  float local_90;
  int local_8c;
  float *local_88;
  float *local_84;
  float *local_80;
  float *local_7c;
  int local_78;
  undefined8 local_74;
  float local_6c;
  int local_68;
  char local_61;
  int local_60;
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bf0b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = *param_1;
  local_1c = param_1[1];
  local_18 = param_1[2];
  local_5c = *param_2;
  local_58 = param_2[1];
  local_54 = param_2[2];
  DAT_02a13c79 = 0;
  local_e8 = 0;
  local_60 = 0;
  if (DAT_008e8e04 == 3) {
    local_94 = FUN_0058bca0();
    local_8 = 0;
    if (local_94 == 0) {
      local_8c = 0;
    }
    else {
      local_8c = FUN_00592010();
    }
    local_c8 = local_8c;
    local_8 = 0xffffffff;
    local_60 = local_8c;
    *(undefined4 *)(local_8c + 0x10) = 0;
    *(undefined4 *)(local_8c + 0x14) = 0;
    FUN_00591fc0();
    local_8 = 1;
    FUN_00592230();
    FUN_00592230();
    local_88 = (float *)FUN_005111d0();
    local_7c = (float *)FUN_005111d0();
    *local_88 = local_20;
    local_88[1] = local_18;
    *local_7c = local_5c;
    local_7c[1] = local_54;
    fVar1 = local_7c[1];
    *(float *)(local_60 + 0x18) = *local_7c;
    *(float *)(local_60 + 0x1c) = fVar1;
    local_b0 = local_60;
    local_8 = 0xffffffff;
    FUN_00417c60();
  }
  else {
    local_61 = FUN_0048fca0(local_20,local_18,local_14);
    for (local_78 = 0; local_78 < 0x10; local_78 = local_78 + 1) {
      cVar2 = FUN_00466290(local_20,local_18,local_5c,local_54,DAT_008e8e0c);
      if (cVar2 != '\0') {
        local_9c = FUN_0058bca0();
        local_8 = 2;
        if (local_9c == 0) {
          local_a4 = 0;
        }
        else {
          local_a4 = FUN_00592010();
        }
        local_b4 = local_a4;
        local_8 = 0xffffffff;
        local_68 = local_a4;
        *(undefined4 *)(local_a4 + 0x10) = 0;
        *(undefined4 *)(local_a4 + 0x14) = 0;
        FUN_00591fc0();
        local_8 = 3;
        FUN_00592230();
        FUN_00592230();
        local_ac = (float *)FUN_005111d0();
        local_84 = (float *)FUN_005111d0();
        *local_ac = local_20;
        local_ac[1] = local_18;
        *local_84 = local_5c;
        local_84[1] = local_54;
        fVar1 = local_84[1];
        *(float *)(local_68 + 0x18) = *local_84;
        *(float *)(local_68 + 0x1c) = fVar1;
        local_bc = local_68;
        local_8 = 0xffffffff;
        FUN_00417c60();
        goto LAB_00590b74;
      }
      local_2c = local_5c;
      local_28 = local_58;
      local_24 = local_54;
      if (local_78 < 1) {
        cVar2 = FUN_00466d40();
        if (cVar2 != '\0') goto LAB_0059076c;
        cVar2 = FUN_0048fca0(local_2c);
        if (cVar2 != local_61) goto LAB_0059076c;
LAB_005909d9:
        if (local_60 != 0) {
          FUN_00590b90();
        }
        local_60 = FUN_0058fe90(&local_20);
        if ((*(uint *)(local_60 + 0x10) & 1) == 0) break;
      }
      else {
LAB_0059076c:
        local_6c = 1.0;
        local_74._0_4_ = local_20 - local_5c;
        local_74._4_4_ = local_18 - local_54;
        if (local_78 < 1) {
          fVar4 = (float10)FUN_00453f80();
          local_c4 = (float)fVar4;
          uVar5 = local_e4;
          local_74 = CONCAT44(local_74._4_4_,(float)local_74);
          if (local_c4 < 0.0001) {
            fVar4 = (float10)FUN_00453f80();
            local_dc = (float)fVar4;
            uVar5 = local_e4;
            local_74 = CONCAT44(local_74._4_4_,(float)local_74);
            if (local_dc < 0.0001) goto LAB_005907f5;
          }
        }
        else {
LAB_005907f5:
          fVar4 = (float10)FUN_004a7890();
          local_b8 = (float)fVar4;
          uVar5 = FUN_008205a0();
          local_6c = DAT_02cc50e0 * 16.0;
          local_d4 = uVar5;
          local_74 = uVar5;
        }
        local_90 = local_6c;
        local_e4 = uVar5;
        puVar3 = (undefined4 *)FUN_00440000(local_124,(float)local_74,0);
        local_38 = *puVar3;
        local_34 = puVar3[1];
        local_30 = puVar3[2];
        puVar3 = (undefined4 *)FUN_0049c4f0(local_13c,local_5c,local_58);
        local_50 = *puVar3;
        local_4c = puVar3[1];
        local_48 = puVar3[2];
        local_44 = puVar3[3];
        local_40 = puVar3[4];
        local_3c = puVar3[5];
        fVar4 = (float10)FUN_00590340(local_61,&local_50,&local_38);
        local_6c = (float)fVar4;
        if (local_6c < local_90) {
          fVar4 = (float10)FUN_00820570((double)((float)local_74 * (float)local_74 +
                                                 local_74._4_4_ * local_74._4_4_ + 1.1754944e-38));
          local_cc = (float)fVar4;
          local_6c = local_cc * 0.5 * DAT_02cc50e0 + local_6c;
          local_2c = (float)local_74 * local_6c + local_2c;
          local_24 = local_74._4_4_ * local_6c + local_24;
          local_c0 = local_cc;
          goto LAB_005909d9;
        }
      }
    }
    if (local_60 == 0) {
      local_a0 = FUN_0058bca0();
      local_8 = 4;
      if (local_a0 == 0) {
        local_98 = 0;
      }
      else {
        local_98 = FUN_00592010();
      }
      local_d8 = local_98;
      local_8 = 0xffffffff;
      local_60 = local_98;
      *(undefined4 *)(local_98 + 0x10) = 1;
      FUN_00591fc0();
      local_8 = 5;
      FUN_00592230();
      FUN_00592230();
      local_a8 = (float *)FUN_005111d0();
      local_80 = (float *)FUN_005111d0();
      *local_a8 = local_20;
      local_a8[1] = local_18;
      *local_80 = local_5c;
      local_80[1] = local_54;
      fVar1 = local_80[1];
      *(float *)(local_60 + 0x18) = *local_80;
      *(float *)(local_60 + 0x1c) = fVar1;
      *(undefined4 *)(local_60 + 0x14) = 0;
      local_8 = 0xffffffff;
      FUN_00417c60();
    }
    FUN_0058f540(local_20,local_18,local_5c,local_54,0);
  }
LAB_00590b74:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

