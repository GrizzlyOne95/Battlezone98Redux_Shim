
void __fastcall FUN_005bc170(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_354 [64];
  undefined1 local_314 [64];
  undefined1 local_2d4 [64];
  undefined1 local_294 [64];
  undefined8 local_254;
  undefined4 local_24c;
  int local_248;
  undefined4 local_244;
  int local_240;
  int local_23c;
  int local_238;
  undefined4 local_234;
  int local_230;
  int local_22c;
  int local_228;
  float *local_224;
  undefined4 local_220 [16];
  undefined4 local_1e0 [16];
  undefined4 local_1a0 [16];
  undefined4 local_160 [16];
  undefined4 local_120 [16];
  undefined4 local_e0 [16];
  undefined4 local_a0 [6];
  float local_88;
  float local_84;
  float local_80;
  double local_78;
  double local_70;
  double local_68;
  undefined4 local_60 [6];
  float local_48;
  float local_44;
  float local_40;
  double local_38;
  double local_30;
  double local_28;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_228 = param_1;
  if ((((DAT_008eaad8 == 0) || (DAT_008eaad8 == 2)) || (DAT_008eaad8 == 1)) || (DAT_008eaad8 == 7))
  {
    local_224 = (float *)FUN_00439e60();
    iVar1 = ___scrt_is_user_matherr_present();
    local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254);
    if ((iVar1 == 0) &&
       (local_254 = CONCAT44(local_254._4_4_,(undefined4)local_254), DAT_008eaab0 != 0)) {
      puVar2 = (undefined4 *)FUN_0081fe60(local_294,local_228 + 0x28,local_224 + 0x10);
      puVar3 = local_e0;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_e0;
      puVar3 = local_a0;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      local_14 = (float)((double)(local_88 * 12.0) + local_78);
      local_10 = (float)((double)(local_84 * 12.0) + local_70);
      local_c = (float)((double)(local_80 * 12.0) + local_68);
      if (0.0001 < local_c) {
        FUN_0049bf10((local_224[2] * local_14) / local_c + *local_224);
        local_24c = FUN_0083f040();
        FUN_0049bf10((local_224[3] * local_10) / local_c + local_224[1]);
        local_244 = FUN_0083f040();
        FUN_0068c560(local_224[0xe],*(undefined4 *)(local_228 + 0xc4),local_24c,local_244,0x250004,0
                    );
      }
      if (*(int *)(local_228 + 200) != 0) {
        puVar2 = (undefined4 *)FUN_0081fe60(local_314,local_228 + 0x68,local_224 + 0x10);
        puVar3 = local_120;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_120;
        puVar3 = local_1e0;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        local_254 = FUN_00689eb0();
        FUN_0049bf10((float)local_254 * 40.0);
        local_240 = FUN_0083f040();
        for (local_22c = -0x1e; local_22c < 0x1f; local_22c = local_22c + 5) {
          puVar2 = (undefined4 *)FUN_0081ec40(local_2d4,(float)local_22c * 0.017453292);
          puVar3 = local_160;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          puVar2 = local_160;
          puVar3 = local_220;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          puVar2 = (undefined4 *)FUN_0081fe60(local_354,local_220,local_1e0);
          puVar3 = local_1a0;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          puVar2 = local_1a0;
          puVar3 = local_60;
          for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          local_20 = (float)((double)(local_48 * 12.0) + local_38);
          local_1c = (float)((double)(local_44 * 12.0) + local_30);
          local_18 = (float)((double)(local_40 * 12.0) + local_28);
          if (0.0001 < local_18) {
            FUN_0049bf10((local_224[2] * local_20) / local_18 + *local_224);
            local_238 = FUN_0083f040();
            FUN_0049bf10((local_224[3] * local_1c) / local_18 + local_224[1]);
            local_234 = FUN_0083f040();
            if (local_22c == 0) {
              local_23c = *(int *)(local_228 + 200);
            }
            else {
              local_23c = *(int *)(local_228 + 200) + 2;
            }
            local_230 = local_23c;
            local_248 = local_23c + 1;
            FUN_0068c560(local_224[0xe],local_23c,local_238 - local_240,local_234,0x240004,0);
            FUN_0068c560(local_224[0xe],local_248,local_238 + local_240,local_234,0x260004,0);
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

