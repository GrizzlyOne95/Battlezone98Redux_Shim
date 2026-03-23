
void FUN_006e9190(void)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  int iVar5;
  uint uVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar7;
  basic_ostream<char,struct_std::char_traits<char>_> local_354 [176];
  undefined1 auStack_2a4 [176];
  undefined1 auStack_1f4 [176];
  undefined4 local_144;
  undefined1 *local_13c;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  basic_ostream<char,struct_std::char_traits<char>_> *local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined1 *local_d8;
  undefined4 local_d4;
  undefined1 *local_d0;
  undefined1 *local_cc;
  uint local_c8;
  uint local_b8;
  undefined4 local_b4;
  uint local_b0;
  uint local_ac;
  int local_a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [96];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085498b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_b0 = 0;
  FUN_006d1110();
  local_8 = 0;
  if (*(char *)(local_a8 + 0x4ab8) == '\0') {
    FUN_006f8b30();
    local_8._0_1_ = 1;
    while (cVar1 = FUN_006ab7d0(), cVar1 != '\0') {
      FUN_006f2e90();
      FUN_00421ec0();
      cVar1 = FUN_006f2d90();
      if (cVar1 == '\0') {
        local_fc = FUN_006f8b30();
        FID_conflict_operator_();
        FUN_006ca8c0();
      }
      else {
        local_f4 = FUN_0068b0a0();
        FID_conflict_operator_();
        FUN_006ca8c0();
      }
    }
    cVar1 = FUN_0041fc90();
    if (cVar1 == '\0') {
      *(undefined1 *)(local_a8 + 0x4ab8) = 1;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      FUN_006d1140();
      FUN_00422170();
      puVar2 = (undefined4 *)FID_conflict_begin();
      local_b4 = *puVar2;
      while( true ) {
        FID_conflict_end();
        cVar1 = FID_conflict_operator__();
        if (cVar1 == '\0') break;
        FUN_00421ec0();
        FUN_00421ec0();
        local_dc = FUN_004b4350();
        FUN_00421ec0();
        FUN_00421ec0();
        local_d4 = FUN_006cc070();
        FUN_004170c0();
        FUN_0041f870();
        FUN_00416430();
        FUN_006e6cb0();
        FUN_004170c0();
        FUN_0041f870();
        FUN_00416430();
        FUN_006e6cb0();
        FUN_00496500();
      }
      cVar1 = FUN_006d4590();
      if ((cVar1 != '\0') && (cVar1 = FUN_006d45c0(), cVar1 != '\0')) {
        FUN_00574400();
        local_8 = 2;
        FUN_00574400();
        local_8._0_1_ = 3;
        FUN_00574400();
        local_8._0_1_ = 4;
        if (&stack0x00000000 == (undefined1 *)0x364) {
          local_e4 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
        }
        else {
          local_e4 = local_354;
        }
        uVar3 = FUN_0067ac40();
        pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar3);
        FUN_004bc590();
        if (&stack0x00000000 == (undefined1 *)0x2b4) {
          local_cc = (undefined1 *)0x0;
        }
        else {
          local_cc = auStack_2a4;
        }
        FUN_004bc590();
        if (&stack0x00000000 == (undefined1 *)0x204) {
          local_d0 = (undefined1 *)0x0;
        }
        else {
          local_d0 = auStack_1f4;
        }
        FUN_004bc590();
        local_b8 = 0;
        local_c8 = 0;
        local_ac = 0;
        while (uVar3 = FUN_0067ac40(), local_ac < uVar3) {
          FUN_0067ac60();
          FUN_00421ec0();
          FUN_004b4350();
          iVar5 = FUN_004170c0();
          local_b8 = iVar5 + local_b8;
          FUN_0067ac60();
          FUN_00421ec0();
          FUN_006cc070();
          iVar5 = FUN_004170c0();
          local_c8 = iVar5 + local_c8;
          if (&stack0x00000000 == (undefined1 *)0x2b4) {
            local_d8 = (undefined1 *)0x0;
          }
          else {
            local_d8 = auStack_2a4;
          }
          FUN_0067ac60();
          FUN_00421ec0();
          FUN_004b4350();
          local_10c = FUN_006b6520();
          local_8._0_1_ = 5;
          local_104 = local_10c;
          FUN_0067ac60();
          FUN_00421ec0();
          FUN_004b4350();
          uVar6 = FUN_004170c0();
          uVar3 = local_ac;
          pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                   FUN_004bc590(local_d8,&DAT_00871534);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar3);
          pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar6);
          FUN_004bc590();
          FUN_00574730();
          FUN_004bc590();
          local_8._0_1_ = 4;
          ~basic_string<>();
          cVar1 = FUN_006d4590();
          if ((cVar1 != '\0') && (cVar1 = FUN_006d45c0(), cVar1 != '\0')) {
            FUN_0067ac60();
            FUN_00421ec0();
            iVar5 = FUN_006cc050();
            if (iVar5 == 1) {
              FUN_0067ac60();
              FUN_00421ec0();
              pbVar7 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)FUN_006cc070();
              local_11c = std::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          ::
                          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                    (local_74,pbVar7);
              local_8 = CONCAT31(local_8._1_3_,6);
              local_b0 = local_b0 | 1;
              local_114 = local_11c;
              local_e0 = local_11c;
            }
            else {
              FUN_0067ac60();
              FUN_00421ec0();
              FUN_006cc070();
              local_124 = FUN_006b6520();
              local_8 = 7;
              local_b0 = local_b0 | 2;
              local_118 = local_124;
              local_e0 = local_124;
            }
            local_ec = local_e0;
            if (&stack0x00000000 == (undefined1 *)0x204) {
              local_e8 = (undefined1 *)0x0;
            }
            else {
              local_e8 = auStack_1f4;
            }
            FUN_0067ac60();
            FUN_00421ec0();
            iVar5 = FUN_006cc050();
            FUN_0067ac60();
            FUN_00421ec0();
            FUN_006cc070();
            uVar6 = FUN_004170c0();
            uVar3 = local_ac;
            pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                     FUN_004bc590(local_e8,&DAT_00871534,local_ac,&DAT_00899010);
            pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                               (pbVar4,uVar3);
            pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar4);
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar6);
            pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,iVar5);
            FUN_004bc590();
            FUN_00574730();
            FUN_004bc590();
            local_8 = 6;
            if ((local_b0 & 2) != 0) {
              local_b0 = local_b0 & 0xfffffffd;
              ~basic_string<>();
            }
            local_8._0_1_ = 4;
            local_8._1_3_ = 0;
            if ((local_b0 & 1) != 0) {
              local_b0 = local_b0 & 0xfffffffe;
              ~basic_string<>();
            }
          }
          local_ac = local_ac + 1;
        }
        uVar3 = local_c8;
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_354,local_b8);
        pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar3);
        FUN_004bc590();
        local_110 = GetPolicy();
        local_8._0_1_ = 8;
        local_f8 = local_110;
        FUN_006d4480();
        local_8._0_1_ = 4;
        ~basic_string<>();
        local_120 = GetPolicy();
        local_8._0_1_ = 9;
        local_100 = local_120;
        FUN_006d4480();
        local_8._0_1_ = 4;
        ~basic_string<>();
        local_108 = GetPolicy();
        local_8._0_1_ = 10;
        local_f0 = local_108;
        FUN_006d4480();
        local_8._0_1_ = 4;
        ~basic_string<>();
        local_8._0_1_ = 3;
        FUN_00417f10();
        local_8 = CONCAT31(local_8._1_3_,2);
        FUN_00417f10();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      local_13c = &stack0xfffffc80;
      local_144 = function<>(local_a8 + 0x8e8);
      FUN_006f2a90(local_a8 + 0x4aa0);
    }
    else {
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006ca8c0();
      local_8 = 0xffffffff;
      FUN_006d1140();
    }
  }
  else {
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

