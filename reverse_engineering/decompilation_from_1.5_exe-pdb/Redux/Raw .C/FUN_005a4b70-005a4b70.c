
void __fastcall FUN_005a4b70(int param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char cVar10;
  undefined4 *puVar11;
  int iVar12;
  float *pfVar13;
  float10 fVar14;
  undefined1 local_94 [12];
  undefined1 local_88 [12];
  float local_7c;
  float local_78;
  float local_74;
  float *local_70;
  int local_6c;
  int local_68;
  float *local_64;
  int local_60;
  undefined8 local_5c;
  undefined8 local_54;
  undefined8 local_4c;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_60 = param_1;
  (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  cVar10 = FUN_00466d40();
  if (cVar10 == '\0') {
    FUN_00601200();
    *(undefined4 *)(local_60 + 8) = 0xd;
  }
  else if (*(int *)(local_60 + 8) != 0xd) {
    if (*(int *)(local_60 + 0x14) != 0) {
      local_6c = FUN_00462630();
      if (local_6c == 0) {
        FUN_00601200();
        *(undefined4 *)(local_60 + 8) = 0xd;
        goto LAB_005a4f12;
      }
      puVar11 = (undefined4 *)(**(code **)(*(int *)(local_6c + 0x18) + 0xc))();
      *(undefined4 *)(local_60 + 0x28) = *puVar11;
      *(undefined4 *)(local_60 + 0x2c) = puVar11[1];
      *(undefined4 *)(local_60 + 0x30) = puVar11[2];
      iVar12 = FUN_0045bdf0();
      if (iVar12 != 0) {
        FUN_00601200();
        *(undefined4 *)(local_60 + 8) = 0xd;
        goto LAB_005a4f12;
      }
    }
    local_70 = (float *)(*(int *)(*(int *)(local_60 + 0x10) + 0x230) + 0xc4);
    local_68 = FUN_0045c4d0();
    local_64 = (float *)FUN_004624b0();
    local_20 = *(float *)(local_60 + 0x28);
    local_1c = *(undefined4 *)(local_60 + 0x2c);
    local_18 = *(float *)(local_60 + 0x30);
    if (local_64[1] <= 0.0 && local_64[1] != 0.0) {
      uVar1 = *(undefined8 *)(local_68 + 0x28);
      uVar2 = *(undefined8 *)(local_68 + 0x30);
      uVar3 = *(undefined8 *)(local_68 + 0x38);
      local_74 = 10.0;
      local_5c._0_4_ = (undefined4)uVar1;
      local_5c._4_4_ = (undefined4)((ulonglong)uVar1 >> 0x20);
      uVar4 = local_5c._4_4_;
      local_54._0_4_ = (undefined4)uVar2;
      local_54._4_4_ = (undefined4)((ulonglong)uVar2 >> 0x20);
      uVar5 = local_54._4_4_;
      local_4c._0_4_ = (undefined4)uVar3;
      local_4c._4_4_ = (undefined4)((ulonglong)uVar3 >> 0x20);
      uVar6 = local_4c._4_4_;
      uVar7 = (undefined4)local_5c;
      local_5c = uVar1;
      uVar8 = (undefined4)local_54;
      local_54 = uVar2;
      uVar9 = (undefined4)local_4c;
      local_4c = uVar3;
      iVar12 = FUN_00784620(uVar7,uVar4,uVar8,uVar5,uVar9,uVar6,*local_64,local_64[1],local_64[2],
                            &local_74,0);
      if (iVar12 != 0) {
        local_20 = local_20 - local_74 * *local_64;
        local_18 = local_18 - local_74 * local_64[2];
      }
    }
    pfVar13 = (float *)FUN_00445260(local_94,&local_20,local_68);
    local_38 = *pfVar13;
    local_34 = pfVar13[1];
    local_30 = pfVar13[2];
    local_14 = local_38;
    local_10 = local_34;
    local_c = local_30;
    pfVar13 = (float *)FUN_00440300(local_88,local_64,local_68);
    local_44 = *pfVar13;
    local_40 = pfVar13[1];
    local_3c = pfVar13[2];
    local_2c = local_44;
    local_28 = local_40;
    local_24 = local_3c;
    fVar14 = (float10)FUN_00447ed0(local_14 * 0.2 - local_44 * 0.2,0xbf800000,0x3f800000);
    local_70[2] = (float)fVar14;
    fVar14 = (float10)FUN_00447ed0(local_c * 0.2 - local_3c * 0.2,0xbf800000,0x3f800000);
    local_70[3] = (float)fVar14;
    fVar14 = (float10)FUN_00820570((double)(local_14 * local_14 + local_c * local_c + 0.0001));
    local_7c = (float)fVar14;
    local_78 = local_14 * local_7c * 5.0;
    iVar12 = FUN_0045c490(0xbf800000,0x3f800000);
    fVar14 = (float10)FUN_00447ed0(local_78 - *(float *)(iVar12 + 0x28));
    *local_70 = (float)fVar14;
  }
LAB_005a4f12:
  FUN_0083e885();
  return;
}

