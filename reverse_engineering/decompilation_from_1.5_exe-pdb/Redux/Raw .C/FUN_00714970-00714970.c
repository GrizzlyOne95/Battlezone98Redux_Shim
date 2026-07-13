
void FUN_00714970(char *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 *puStack_270;
  char *pcStack_26c;
  undefined4 *puStack_268;
  undefined1 *puStack_264;
  char *pcStack_260;
  char *pcStack_25c;
  uint uStack_258;
  undefined1 auStack_244 [160];
  undefined1 local_1a4 [8];
  undefined1 *local_19c;
  undefined1 *local_198;
  undefined1 local_194 [8];
  undefined4 local_18c;
  char local_188 [8];
  undefined4 local_180;
  undefined4 local_17c;
  undefined1 *local_178;
  undefined1 local_174 [8];
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  char *local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  char *local_12c;
  int *local_128;
  int *local_124;
  char *local_120;
  int *local_11c;
  undefined1 *local_118;
  int *local_114;
  int *local_110;
  undefined4 local_10c;
  undefined4 local_108;
  char local_101;
  int local_100;
  char local_fc [32];
  undefined1 local_dc [24];
  undefined1 local_c4 [24];
  undefined1 local_ac [24];
  undefined1 local_94 [24];
  undefined1 local_7c [24];
  undefined1 local_64 [24];
  char local_4c [24];
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857fc2;
  local_10 = ExceptionList;
  uStack_258 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_25c = "process handshake request";
  pcStack_260 = (char *)0x400;
  puStack_264 = (undefined1 *)0x7149bc;
  local_14 = uStack_258;
  FUN_006d08b0();
  pcStack_25c = (char *)(local_100 + 0x4abc);
  pcStack_260 = (char *)0x7149ce;
  cVar1 = FUN_00720f90();
  if (cVar1 == '\0') {
    pcStack_25c = "HTTP REQUEST";
    pcStack_260 = (char *)0x400;
    puStack_264 = (undefined1 *)0x7149f7;
    FUN_006d08b0();
    pcStack_25c = (char *)0x714a02;
    cVar1 = FUN_006d3810();
    if (cVar1 == '\0') {
      local_120 = "http";
    }
    else {
      local_120 = "https";
    }
    local_178 = (undefined1 *)&puStack_270;
    local_17c = basic_string<>(local_120);
    pcStack_25c = (char *)FUN_0070f570(local_174,local_100 + 0x4abc);
    pcStack_260 = (char *)0x714a81;
    local_168 = pcStack_25c;
    local_140 = pcStack_25c;
    FID_conflict_operator_();
    pcStack_25c = (char *)0x714a8c;
    FUN_006ca8c0();
    pcStack_25c = (char *)0x714a9d;
    FUN_00421ec0();
    pcStack_25c = (char *)0x714aa4;
    cVar1 = FUN_006b5d20();
    if (cVar1 == '\0') {
      pcStack_25c = "Bad request: failed to parse uri";
      pcStack_260 = (char *)0x400;
      puStack_264 = (undefined1 *)0x714ac6;
      FUN_006d08b0();
      pcStack_25c = (char *)0x190;
      pcStack_260 = (char *)0x714adc;
      FUN_006b9910();
      pcStack_25c = (char *)0x6;
      pcStack_260 = param_1;
      puStack_264 = (undefined1 *)0x714ae7;
      make_error_code();
    }
    else {
      pcStack_25c = (char *)0x714b03;
      cVar1 = FUN_006caba0();
      if (cVar1 == '\0') {
        pcStack_25c = (char *)0x1aa;
        pcStack_260 = (char *)0x714b81;
        FUN_00720530();
        pcStack_25c = (char *)0x1c;
        pcStack_260 = param_1;
        puStack_264 = (undefined1 *)0x714b8c;
        make_error_code();
      }
      else {
        *(undefined1 *)(local_100 + 0x4c30) = 1;
        puStack_264 = (undefined1 *)(local_100 + 0x918);
        local_19c = (undefined1 *)&pcStack_260;
        puStack_268 = (undefined4 *)0x714b33;
        local_180 = shared_ptr<>();
        puStack_264 = (undefined1 *)0x714b4a;
        FUN_006e6250();
        if (*(int *)(local_100 + 0xa20) == 3) {
          pcStack_25c = (char *)0x15;
          pcStack_260 = param_1;
          puStack_264 = (undefined1 *)0x714b64;
          make_error_code();
        }
        else {
          pcStack_25c = (char *)0x714b9f;
          FUN_006ab750();
        }
      }
    }
  }
  else {
    pcStack_25c = (char *)0x714bb8;
    local_11c = (int *)FUN_00421ec0();
    pcStack_25c = (char *)(local_100 + 0x4abc);
    pcStack_260 = (char *)&local_10c;
    puStack_264 = (undefined1 *)0x714be5;
    (**(code **)(*local_11c + 0x14))();
    pcStack_25c = (char *)0x714bf0;
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      pcStack_25c = (char *)0x714cc9;
      FUN_006e48d0();
      local_8 = 2;
      pcStack_25c = (char *)0x714ce1;
      local_128 = (int *)FUN_00421ec0();
      pcStack_25c = (char *)(local_100 + 0x4abc);
      pcStack_260 = local_fc;
      puStack_264 = (undefined1 *)0x714d0d;
      pcStack_25c = (char *)(**(code **)(*local_128 + 0x10))();
      local_8._0_1_ = 3;
      pcStack_260 = (char *)0x714d32;
      local_15c = pcStack_25c;
      local_154 = pcStack_25c;
      FUN_007100a0();
      local_8._0_1_ = 2;
      pcStack_25c = (char *)0x714d41;
      FUN_006e4470();
      pcStack_25c = (char *)0x714d49;
      cVar1 = FUN_006ab7d0();
      if (cVar1 == '\0') {
        pcStack_25c = (char *)0x714e24;
        iVar2 = FUN_004170c0();
        if (iVar2 != 0) {
          pcStack_25c = "Sec-WebSocket-Extensions";
          pcStack_260 = (char *)0x714e35;
          basic_string<>();
          local_8._0_1_ = 6;
          pcStack_25c = local_2c;
          pcStack_260 = local_4c;
          puStack_264 = (undefined1 *)0x714e52;
          FUN_006b7810();
          local_8._0_1_ = 2;
          pcStack_25c = (char *)0x714e5e;
          ~basic_string<>();
        }
        pcStack_25c = (char *)0x714e6f;
        local_124 = (int *)FUN_00421ec0();
        pcStack_25c = (char *)(local_100 + 0x4abc);
        pcStack_260 = local_188;
        puStack_264 = (undefined1 *)0x714e9b;
        pcStack_25c = (char *)(**(code **)(*local_124 + 0x30))();
        pcStack_260 = (char *)0x714eb9;
        local_138 = pcStack_25c;
        FID_conflict_operator_();
        pcStack_25c = (char *)0x714ec4;
        FUN_006ca8c0();
        pcStack_25c = (char *)0x714ed5;
        FUN_00421ec0();
        pcStack_25c = (char *)0x714edc;
        cVar1 = FUN_006b5d20();
        if (cVar1 == '\0') {
          pcStack_25c = "Bad request: failed to parse uri";
          pcStack_260 = (char *)0x400;
          puStack_264 = (undefined1 *)0x714efe;
          FUN_006d08b0();
          pcStack_25c = (char *)0x190;
          pcStack_260 = (char *)0x714f14;
          FUN_006b9910();
          pcStack_25c = (char *)0x6;
          pcStack_260 = param_1;
          puStack_264 = (undefined1 *)0x714f1f;
          make_error_code();
          local_8 = 0xffffffff;
          pcStack_25c = (char *)0x714f31;
          FUN_006e4470();
        }
        else {
          pcStack_25c = (char *)0x714f4a;
          local_110 = (int *)FUN_00421ec0();
          pcStack_25c = (char *)(local_100 + 0x4bd4);
          pcStack_260 = (char *)(local_100 + 0x4abc);
          puStack_264 = local_194;
          puStack_268 = (undefined4 *)0x714f84;
          (**(code **)(*local_110 + 0x2c))();
          pcStack_25c = (char *)0x714f8f;
          FUN_006ab7d0();
          pcStack_25c = (char *)0x714fa0;
          cVar1 = FUN_006caba0();
          if (cVar1 != '\0') {
            puStack_264 = (undefined1 *)(local_100 + 0x918);
            local_198 = (undefined1 *)&pcStack_260;
            puStack_268 = (undefined4 *)0x714fc3;
            local_18c = shared_ptr<>();
            puStack_264 = (undefined1 *)0x714fda;
            local_101 = FUN_0071bac0();
            if (local_101 == '\0') {
              pcStack_25c = "USER REJECT";
              pcStack_260 = (char *)0x400;
              puStack_264 = (undefined1 *)0x715200;
              FUN_006d08b0();
              pcStack_25c = (char *)0x715211;
              iVar2 = FUN_006b8f30();
              if (iVar2 == 0) {
                pcStack_25c = (char *)0x190;
                pcStack_260 = (char *)0x71522b;
                FUN_006b9910();
              }
              pcStack_25c = (char *)0x1b;
              pcStack_260 = param_1;
              puStack_264 = (undefined1 *)0x715236;
              make_error_code();
              local_8 = 0xffffffff;
              pcStack_25c = (char *)0x715248;
              FUN_006e4470();
              goto LAB_00715267;
            }
          }
          pcStack_25c = (char *)0x65;
          pcStack_260 = (char *)0x715002;
          FUN_006b9910();
          pcStack_25c = (char *)0x715013;
          local_114 = (int *)FUN_00421ec0();
          pcStack_25c = (char *)(local_100 + 0x4b40);
          pcStack_260 = (char *)(local_100 + 0x4bbc);
          puStack_264 = (undefined1 *)(local_100 + 0x4abc);
          puStack_268 = (undefined4 *)local_1a4;
          pcStack_26c = (char *)0x715059;
          puVar3 = (undefined4 *)(**(code **)(*local_114 + 0x18))();
          local_10c = *puVar3;
          local_108 = puVar3[1];
          pcStack_25c = (char *)0x715075;
          cVar1 = FUN_006ab7d0();
          if (cVar1 == '\0') {
            pcStack_25c = (char *)0x715255;
            FUN_006ab750();
            local_8 = 0xffffffff;
            pcStack_25c = (char *)0x715264;
            FUN_006e4470();
          }
          else {
            pcStack_25c = (char *)0x1;
            pcStack_260 = (char *)0x3;
            puStack_264 = (undefined1 *)0x71508f;
            FUN_00574400();
            local_8._0_1_ = 7;
            if (&stack0x00000000 == (undefined1 *)0x254) {
              local_118 = (undefined1 *)0x0;
            }
            else {
              local_118 = auStack_244;
            }
            pcStack_25c = local_c4;
            pcStack_260 = (char *)0x7150ca;
            pcStack_260 = (char *)FUN_006ab780();
            local_8._0_1_ = 8;
            pcStack_25c = ")";
            puStack_264 = &DAT_008949c0;
            puStack_268 = &local_10c;
            pcStack_26c = "Processing error: ";
            puStack_270 = local_118;
            local_160 = pcStack_260;
            local_12c = pcStack_260;
            pcStack_26c = (char *)FUN_004bc590();
            puStack_270 = (undefined1 *)0x715112;
            puStack_268 = (undefined4 *)FUN_006f01a0();
            pcStack_26c = (char *)0x71511b;
            puStack_264 = (undefined1 *)FUN_004bc590();
            puStack_268 = (undefined4 *)0x715124;
            pcStack_260 = (char *)FUN_00574730();
            puStack_264 = (undefined1 *)0x71512d;
            FUN_004bc590();
            local_8._0_1_ = 7;
            pcStack_25c = (char *)0x71513f;
            ~basic_string<>();
            pcStack_25c = local_ac;
            pcStack_260 = (char *)0x715151;
            pcStack_25c = (char *)GetPolicy();
            local_8._0_1_ = 9;
            pcStack_260 = (char *)0x400;
            puStack_264 = (undefined1 *)0x715184;
            local_158 = pcStack_25c;
            local_148 = pcStack_25c;
            FUN_006d4480();
            local_8._0_1_ = 7;
            pcStack_25c = (char *)0x715193;
            ~basic_string<>();
            pcStack_25c = (char *)0x1f4;
            pcStack_260 = (char *)0x7151a9;
            FUN_006b9910();
            *(undefined4 *)param_1 = local_10c;
            *(undefined4 *)(param_1 + 4) = local_108;
            local_8 = CONCAT31(local_8._1_3_,2);
            pcStack_25c = (char *)0x7151cc;
            FUN_00417f10();
            local_8 = 0xffffffff;
            pcStack_25c = (char *)0x7151db;
            FUN_006e4470();
          }
        }
      }
      else {
        pcStack_25c = local_dc;
        pcStack_260 = (char *)0x714d63;
        pcStack_25c = (char *)FUN_006ab780();
        local_8._0_1_ = 4;
        pcStack_260 = "Bad request: ";
        puStack_264 = local_7c;
        puStack_268 = (undefined4 *)0x714d8e;
        local_16c = pcStack_25c;
        local_164 = pcStack_25c;
        pcStack_25c = (char *)FUN_006dd7f0();
        local_8._0_1_ = 5;
        pcStack_260 = (char *)0x400;
        puStack_264 = (undefined1 *)0x714dc4;
        local_150 = pcStack_25c;
        local_130 = pcStack_25c;
        FUN_006d4480();
        local_8._0_1_ = 4;
        pcStack_25c = (char *)0x714dd0;
        ~basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,2);
        pcStack_25c = (char *)0x714ddf;
        ~basic_string<>();
        pcStack_25c = (char *)0x190;
        pcStack_260 = (char *)0x714df5;
        FUN_006b9910();
        *(undefined4 *)param_1 = local_34;
        *(undefined4 *)(param_1 + 4) = local_30;
        local_8 = 0xffffffff;
        pcStack_25c = (char *)0x714e12;
        FUN_006e4470();
      }
    }
    else {
      pcStack_25c = local_94;
      pcStack_260 = (char *)0x714c0d;
      pcStack_25c = (char *)FUN_006ab780();
      local_8 = 0;
      pcStack_260 = "Bad request ";
      puStack_264 = local_64;
      puStack_268 = (undefined4 *)0x714c3b;
      local_13c = pcStack_25c;
      local_134 = pcStack_25c;
      pcStack_25c = (char *)FUN_006dd7f0();
      local_8._0_1_ = 1;
      pcStack_260 = (char *)0x400;
      puStack_264 = (undefined1 *)0x714c71;
      local_14c = pcStack_25c;
      local_144 = pcStack_25c;
      FUN_006d4480();
      local_8 = (uint)local_8._1_3_ << 8;
      pcStack_25c = (char *)0x714c7d;
      ~basic_string<>();
      local_8 = 0xffffffff;
      pcStack_25c = (char *)0x714c8f;
      ~basic_string<>();
      pcStack_25c = (char *)0x190;
      pcStack_260 = (char *)0x714ca5;
      FUN_006b9910();
      *(undefined4 *)param_1 = local_10c;
      *(undefined4 *)(param_1 + 4) = local_108;
    }
  }
LAB_00715267:
  ExceptionList = local_10;
  uStack_258 = 0x71527c;
  FUN_0083e885();
  return;
}

