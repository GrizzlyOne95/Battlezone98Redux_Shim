
void FUN_0068e600(int param_1,float *param_2,float param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  float fVar13;
  int local_36c;
  int local_364;
  int local_360;
  float *local_35c;
  float local_358;
  float local_354;
  float local_350;
  float local_34c;
  float local_348;
  float local_340;
  float local_33c;
  float local_338;
  float fStack_334;
  float fStack_330;
  float local_328;
  float local_324;
  float local_320;
  float fStack_31c;
  float fStack_318;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  fVar1 = *param_2;
  fVar2 = param_2[2];
  iVar7 = FUN_00684ce0(0);
  if (iVar7 != 0) {
    if ((param_4 < 0) || (DAT_00920f00 <= param_4)) {
      param_4 = 0;
    }
    param_4 = param_4 * 0x24;
    DAT_00920efc = (uint)(&PTR_DAT_008ed788)[*(uint *)(&DAT_025f8f58 + param_4) & 0xf] | 0xff000000;
    fVar3 = *(float *)(&DAT_025f8f48 + param_4);
    fVar4 = *(float *)(&DAT_025f8f4c + param_4);
    fVar5 = *(float *)(&DAT_025f8f50 + param_4);
    fVar6 = *(float *)(&DAT_025f8f54 + param_4);
    if (1e-05 <= param_3) {
      fVar13 = 0.5 / param_3;
      FUN_0049bf10((*param_2 - param_3) * DAT_02cc50e4);
      iVar7 = FUN_0083f040();
      FUN_0049bf10((param_2[2] - param_3) * DAT_02cc50e4);
      local_360 = FUN_0083f040();
      FUN_0049bf10((*param_2 + param_3) * DAT_02cc50e4);
      iVar8 = FUN_0083f040();
      FUN_0049bf10((param_2[2] + param_3) * DAT_02cc50e4);
      iVar9 = FUN_0083f040();
      FUN_006855e0(&DAT_025f8f38 + param_4,DAT_00920ef4);
      for (local_360 = local_360 + -1; local_360 <= iVar9; local_360 = local_360 + 1) {
        for (local_364 = iVar7 + -1; local_364 <= iVar8; local_364 = local_364 + 1) {
          local_58 = (float)local_364 * DAT_02cc50e0;
          local_50 = (float)local_360 * DAT_02cc50e0;
          puVar10 = (ushort *)FUN_00492d60(local_364,local_360);
          local_54 = (float)(*puVar10 & 0xfff) * 0.1 + 0.1;
          fStack_18 = (local_58 - (fVar1 - param_3)) * fVar13;
          fStack_28 = (local_50 - (fVar2 - param_3)) * fVar13;
          local_40 = (float)(local_364 + 1) * DAT_02cc50e0;
          local_38 = (float)(local_360 + 1) * DAT_02cc50e0;
          puVar10 = (ushort *)FUN_00492d60(local_364 + 1,local_360 + 1);
          local_3c = (float)(*puVar10 & 0xfff) * 0.1 + 0.1;
          fStack_10 = (local_40 - (fVar1 - param_3)) * fVar13;
          fStack_20 = (local_38 - (fVar2 - param_3)) * fVar13;
          local_4c = local_40;
          local_44 = local_50;
          puVar10 = (ushort *)FUN_00492d60(local_364 + 1,local_360);
          local_48 = (float)(*puVar10 & 0xfff) * 0.1 + 0.1;
          fStack_14 = fStack_10;
          fStack_24 = fStack_28;
          local_34 = local_58;
          local_2c = local_38;
          puVar10 = (ushort *)FUN_00492d60(local_364,local_360 + 1);
          local_30 = (float)(*puVar10 & 0xfff) * 0.1 + 0.1;
          fStack_c = fStack_18;
          fStack_1c = fStack_20;
          FUN_00820180(&local_58,&local_58,4,param_1 + 0x40);
          uVar11 = FUN_007816d0(&local_58,&local_4c,&local_40,&local_34);
          if ((uVar11 & 1) != 0) {
            local_358 = local_58;
            local_354 = local_54;
            local_350 = local_50;
            local_340 = local_4c;
            local_33c = local_48;
            local_338 = local_44;
            local_328 = local_40;
            local_324 = local_3c;
            local_320 = local_38;
            local_34c = fStack_18;
            fStack_334 = fStack_14;
            fStack_31c = fStack_10;
            local_348 = fStack_28;
            fStack_330 = fStack_24;
            fStack_318 = fStack_20;
            iVar12 = FUN_0068d690(&local_358,&local_358,3);
            if (0 < iVar12) {
              local_35c = &local_358;
              for (local_36c = iVar12; 0 < local_36c; local_36c = local_36c + -1) {
                local_35c[3] = local_35c[3] * (fVar5 - fVar3) + fVar3;
                local_35c[4] = local_35c[4] * (fVar6 - fVar4) + fVar4;
                local_35c[5] = 1.0;
                local_35c = local_35c + 6;
              }
              FUN_00686830(param_1,&local_358,iVar12,DAT_00920efc);
            }
          }
          if ((uVar11 & 2) != 0) {
            local_358 = local_58;
            local_354 = local_54;
            local_350 = local_50;
            local_340 = local_40;
            local_33c = local_3c;
            local_338 = local_38;
            local_328 = local_34;
            local_324 = local_30;
            local_320 = local_2c;
            local_34c = fStack_18;
            fStack_334 = fStack_10;
            fStack_31c = fStack_c;
            local_348 = fStack_28;
            fStack_330 = fStack_20;
            fStack_318 = fStack_1c;
            iVar12 = FUN_0068d690(&local_358,&local_358,3);
            if (0 < iVar12) {
              local_35c = &local_358;
              for (local_36c = iVar12; 0 < local_36c; local_36c = local_36c + -1) {
                local_35c[3] = local_35c[3] * (fVar5 - fVar3) + fVar3;
                local_35c[4] = local_35c[4] * (fVar6 - fVar4) + fVar4;
                local_35c[5] = 1.0;
                local_35c = local_35c + 6;
              }
              FUN_00686830(param_1,&local_358,iVar12,DAT_00920efc);
            }
          }
        }
      }
      FUN_006856e0();
      DAT_00920efc = 0xffffff;
    }
  }
  FUN_0083e885();
  return;
}

