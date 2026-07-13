
void FUN_0076e6c0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined4 uStack_b8;
  undefined1 *puStack_b4;
  undefined1 *puStack_b0;
  undefined *puStack_ac;
  uint uVar6;
  undefined1 local_98 [4];
  undefined1 *local_94;
  undefined1 local_8c [4];
  undefined1 local_88 [8];
  undefined4 local_80;
  undefined4 local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  char local_62;
  char local_61;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085dcc8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1 == 0) {
    local_94 = (undefined1 *)&uStack_b8;
    basic_string<>(param_2);
    local_62 = FUN_004883c0();
    local_61 = local_62;
    if (local_62 == '\0') {
      local_68 = 0xffffffff;
      local_6c = 0;
      while (uVar2 = FUN_004170c0(), local_6c < uVar2) {
        iVar3 = FUN_00752d30();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_44,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iVar3 + 0x6c));
        local_8 = 0;
        puStack_ac = (undefined *)0x76e7a8;
        iVar3 = FUN_00489f20();
        if (iVar3 != -1) {
          uVar6 = 0xffffffff;
          puStack_ac = &DAT_008752b0;
          puStack_b0 = (undefined1 *)0x76e7ca;
          uVar2 = FUN_00489f20();
          puStack_ac = (undefined *)0x76e7d3;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                    (local_44,uVar2,uVar6);
          FID_conflict_operator_();
        }
        basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,1);
        puStack_ac = (undefined *)0x76e7ff;
        iVar3 = FUN_00489f20();
        if (iVar3 != -1) {
          uVar6 = 0xffffffff;
          puStack_ac = &DAT_008752b0;
          puStack_b0 = (undefined1 *)0x76e822;
          uVar2 = FUN_00489f20();
          puStack_ac = (undefined *)0x76e82b;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                    (local_2c,uVar2,uVar6);
          FID_conflict_operator_();
        }
        puStack_ac = (undefined *)0x76e847;
        local_74 = FUN_00489f20();
        puStack_ac = (undefined *)0x76e85e;
        local_78 = FUN_00489f20();
        if ((local_74 < local_78) && (local_74 != 0xffffffff)) {
          local_74 = local_78;
        }
        if (local_74 != 0xffffffff) {
          puStack_ac = (undefined *)local_74;
          puStack_b0 = local_8c;
          puStack_b4 = local_98;
          uStack_b8 = 0x76e8a8;
          FID_conflict_begin();
          puStack_b4 = (undefined1 *)0x76e8af;
          FID_conflict_operator_();
          puStack_ac = (undefined *)0x76e8b6;
          puVar4 = (undefined4 *)FID_conflict_operator_();
          local_80 = *puVar4;
          puVar4 = (undefined4 *)FID_conflict_begin();
          local_7c = *puVar4;
          puStack_ac = local_88;
          puStack_b0 = (undefined1 *)0x76e8e3;
          FUN_0071b880();
        }
        puStack_ac = (undefined *)0x76e8f0;
        cVar1 = FUN_00427310();
        if (cVar1 != '\0') {
          local_68 = local_6c;
          local_8 = (uint)local_8._1_3_ << 8;
          ~basic_string<>();
          local_8 = 0xffffffff;
          ~basic_string<>();
          break;
        }
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
        local_6c = local_6c + 1;
      }
      if (local_68 == 0xffffffff) {
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_00482850();
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_5c,pbVar5);
        local_8 = 2;
        local_70 = 0;
        while (uVar2 = FUN_004170c0(), local_70 < uVar2) {
          puStack_ac = (undefined *)0x76e9ad;
          FUN_0076f540();
          puStack_ac = (undefined *)0x76e9b6;
          cVar1 = FUN_00427310();
          if (cVar1 != '\0') {
            local_68 = local_70;
            break;
          }
          local_70 = local_70 + 1;
        }
        if (local_68 != 0xffffffff) {
          FUN_0076f540();
          FUN_0076ae60();
        }
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        FUN_00752d30();
        FUN_0076a600();
      }
    }
    else {
      FUN_0076a030();
    }
  }
  else {
    FUN_0076e4a0();
    FUN_0076b350();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

