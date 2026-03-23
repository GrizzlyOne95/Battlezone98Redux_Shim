
/* WARNING: Removing unreachable block (ram,0x0070a101) */

void FUN_007099f0(undefined4 *param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  uint uVar5;
  int iVar6;
  undefined1 *puStack_514;
  uint uVar7;
  undefined1 auStack_4f0 [176];
  undefined1 auStack_440 [176];
  undefined1 auStack_390 [176];
  undefined1 auStack_2e0 [176];
  undefined1 auStack_230 [184];
  error_condition local_178 [8];
  error_condition local_170 [8];
  error_condition local_168 [8];
  undefined4 local_160;
  undefined1 *local_15c;
  undefined1 *local_158;
  undefined1 *local_154;
  error_condition local_150 [8];
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined1 *local_100;
  undefined1 *local_fc;
  undefined1 *local_f8;
  undefined1 *local_f4;
  shared_ptr<class___ExceptionPtr> local_f0 [8];
  undefined1 *local_e8;
  int *local_e4;
  int *local_e0;
  int *local_dc;
  undefined1 *local_d8;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  uint local_c4;
  int local_c0;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008574e3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_cc = *param_1;
  local_c8 = param_1[1];
  cVar1 = FUN_006ab7d0();
  if ((cVar1 == '\0') && (*(int *)(local_c0 + 0xa24) != 7)) {
    puVar3 = (undefined4 *)make_error_code();
    local_cc = *puVar3;
    local_c8 = puVar3[1];
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_c4 = 0;
    cVar1 = FUN_006d4590();
    if (cVar1 != '\0') {
      FUN_00574400();
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0x450) {
        local_f4 = (undefined1 *)0x0;
      }
      else {
        local_f4 = auStack_440;
      }
      puStack_514 = &DAT_00899bf4;
      uVar5 = local_c4;
      uVar7 = param_2;
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(local_f4);
      puStack_514 = (undefined1 *)0x709cde;
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar5);
      puStack_514 = (undefined1 *)0x709ce4;
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar7);
      local_11c = GetPolicy();
      local_8._0_1_ = 1;
      local_118 = local_11c;
      FUN_006d4480();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    while (local_c4 < param_2) {
      cVar1 = FUN_006d4590();
      if (cVar1 != '\0') {
        FUN_00574400();
        local_8 = 2;
        if (&stack0x00000000 == (undefined1 *)0x240) {
          local_fc = (undefined1 *)0x0;
        }
        else {
          local_fc = auStack_230;
        }
        uVar5 = param_2 - local_c4;
        puStack_514 = local_fc;
        pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar5);
        FUN_004bc590();
        local_13c = GetPolicy();
        local_8._0_1_ = 3;
        local_124 = local_13c;
        FUN_006d4480();
        local_8 = CONCAT31(local_8._1_3_,2);
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      FUN_006ab750();
      cVar1 = FUN_006d4590();
      if (cVar1 != '\0') {
        FUN_00574400();
        local_8 = 4;
        if (&stack0x00000000 == (undefined1 *)0x2f0) {
          local_100 = (undefined1 *)0x0;
        }
        else {
          local_100 = auStack_2e0;
        }
        puStack_514 = (undefined1 *)0x709ee5;
        local_134 = FUN_006b6650();
        local_8._0_1_ = 5;
        puStack_514 = (undefined1 *)0x709f16;
        local_110 = local_134;
        FUN_004bc590();
        FUN_00574730();
        local_8._0_1_ = 4;
        ~basic_string<>();
        local_120 = GetPolicy();
        local_8._0_1_ = 6;
        local_10c = local_120;
        FUN_006d4480();
        local_8 = CONCAT31(local_8._1_3_,4);
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      local_e4 = (int *)FUN_00421ec0();
      puStack_514 = (undefined1 *)0x709fe0;
      iVar6 = (**(code **)(*local_e4 + 0x34))();
      local_c4 = iVar6 + local_c4;
      cVar1 = FUN_006d4590();
      if (cVar1 != '\0') {
        FUN_00574400();
        local_8 = 7;
        if (&stack0x00000000 == (undefined1 *)0x3a0) {
          local_f8 = (undefined1 *)0x0;
        }
        else {
          local_f8 = auStack_390;
        }
        uVar5 = param_2 - local_c4;
        puStack_514 = (undefined1 *)0x70a063;
        pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar5);
        local_130 = GetPolicy();
        local_8._0_1_ = 8;
        local_128 = local_130;
        FUN_006d4480();
        local_8 = CONCAT31(local_8._1_3_,7);
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        puStack_514 = (undefined1 *)0x70a0fd;
        FUN_006f90a0();
        FUN_006ab750();
        local_140 = FUN_006ab780();
        local_8 = 9;
        puStack_514 = local_d8;
        local_138 = local_140;
        FUN_006bc240();
        puStack_514 = (undefined1 *)0x70a186;
        FUN_006dacd0();
        local_8 = 0xffffffff;
        ~basic_string<>();
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          puStack_514 = (undefined1 *)0x70a1c3;
          FUN_006f90a0();
          FUN_006daf10();
        }
        goto LAB_0070a451;
      }
      local_e0 = (int *)FUN_00421ec0();
      cVar1 = (**(code **)(*local_e0 + 0x38))();
      if (cVar1 != '\0') {
        cVar1 = FUN_006d4590();
        if (cVar1 != '\0') {
          FUN_00574400();
          local_8 = 10;
          if (&stack0x00000000 == (undefined1 *)0x500) {
            local_e8 = (undefined1 *)0x0;
          }
          else {
            local_e8 = auStack_4f0;
          }
          FUN_004bc590();
          local_12c = GetPolicy();
          local_8._0_1_ = 0xb;
          local_114 = local_12c;
          FUN_006d4480();
          local_8 = CONCAT31(local_8._1_3_,10);
          ~basic_string<>();
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        local_dc = (int *)FUN_00421ec0();
        (**(code **)(*local_dc + 0x3c))();
        local_8 = 0xc;
        cVar1 = FUN_006ab7d0();
        if (cVar1 == '\0') {
          FUN_006d08b0();
        }
        else {
          FUN_00421ec0();
          FUN_006cc050();
          cVar1 = FUN_006ba0d0();
          if (cVar1 == '\0') {
            if (*(int *)(local_c0 + 0xa20) == 1) {
              cVar1 = FUN_006caba0();
              if (cVar1 != '\0') {
                local_158 = &stack0xfffffaf4;
                puStack_514 = (undefined1 *)0x70a3cc;
                local_144 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                                      ((shared_ptr<class___ExceptionPtr> *)&stack0xfffffaf4,local_f0
                                      );
                local_15c = (undefined1 *)&puStack_514;
                local_148 = shared_ptr<>(local_c0 + 0x918);
                FUN_007100f0();
              }
            }
            else {
              FUN_006d47b0();
            }
          }
          else {
            local_154 = &stack0xfffffaf4;
            puStack_514 = (undefined1 *)0x70a41e;
            local_160 = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                                  ((shared_ptr<class___ExceptionPtr> *)&stack0xfffffaf4,local_f0);
            FUN_00715890();
          }
        }
        local_8 = 0xffffffff;
        FUN_006ca8c0();
      }
    }
    FUN_00714660();
    goto LAB_0070a451;
  }
  local_d0 = 0x10;
  FUN_006de390();
  bVar2 = std::error_condition::operator==((error_condition *)&local_cc,local_178);
  if (bVar2) {
    if (*(int *)(local_c0 + 0xa20) == 3) {
      FUN_006d08b0();
      goto LAB_0070a451;
    }
    if ((*(int *)(local_c0 + 0xa20) == 2) && (*(char *)(local_c0 + 0x4be0) == '\0')) {
      FUN_006ab750();
      FUN_006daf10();
      goto LAB_0070a451;
    }
  }
  else {
    FUN_006eac90();
    bVar2 = std::error_condition::operator==((error_condition *)&local_cc,local_170);
    if (bVar2) {
      if (*(int *)(local_c0 + 0xa20) == 3) {
        FUN_006d08b0();
        goto LAB_0070a451;
      }
    }
    else {
      FUN_006de390();
      bVar2 = std::error_condition::operator==((error_condition *)&local_cc,local_150);
      if (bVar2) {
        if (*(int *)(local_c0 + 0xa20) == 3) {
          FUN_006ab750();
          FUN_006daf10();
          goto LAB_0070a451;
        }
        local_d0 = 0x10;
      }
      else {
        FUN_006de390();
        bVar2 = std::error_condition::operator==((error_condition *)&local_cc,local_168);
        if (bVar2) {
          local_d0 = 4;
        }
      }
    }
  }
  puStack_514 = (undefined1 *)0x709c35;
  FUN_006f90a0();
  FUN_006daf10();
LAB_0070a451:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

