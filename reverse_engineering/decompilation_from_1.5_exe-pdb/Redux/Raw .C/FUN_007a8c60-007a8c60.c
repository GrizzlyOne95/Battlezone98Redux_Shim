
void FUN_007a8c60(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  uint uVar6;
  float10 fVar7;
  undefined1 *puVar8;
  undefined1 *puStack_1f0;
  undefined *puStack_1ec;
  int iVar9;
  undefined1 auStack_1b0 [160];
  double local_110;
  undefined4 local_104;
  double local_100;
  undefined1 *local_f4;
  float local_f0;
  float local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  float local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  float local_c4;
  undefined1 *local_c0;
  uint local_bc;
  int *local_b8;
  undefined1 *local_b4;
  int *local_b0;
  undefined1 *local_ac;
  undefined1 *local_a8;
  int *local_a4;
  int *local_a0;
  undefined1 *local_9c;
  uint local_98;
  float local_94;
  undefined4 local_8c;
  undefined4 local_88;
  char local_82;
  char local_81;
  int local_80;
  int local_7c;
  char *local_78;
  undefined1 local_74 [72];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008607d6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007a8b70();
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0();
  local_88 = *puVar2;
  while( true ) {
    FID_conflict_begin();
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') break;
    local_8c = FUN_0042de50();
    iVar3 = FUN_0056f900();
    if (iVar3 != 0) {
      FUN_0056f900();
      cVar1 = FUN_0056f780();
      if (cVar1 != '\0') {
        FUN_00742cf0();
        FUN_007d0ea0();
        FUN_007cafa0();
        local_81 = '\0';
        FUN_0042d8c0();
        FID_conflict_begin();
        local_80 = 0;
        while (cVar1 = FUN_00420f10(), cVar1 != '\0') {
          local_7c = FUN_0042de50();
          FUN_00574400();
          local_8 = 0;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                    (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                               *)(local_7c + 0x2c));
          local_8._0_1_ = 1;
          uVar4 = FUN_004170c0();
          if (0x15 < uVar4) {
            std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            resize(local_2c,0x15);
          }
          if (&stack0x00000000 == (undefined1 *)0x1c0) {
            local_b4 = (undefined1 *)0x0;
          }
          else {
            local_b4 = auStack_1b0;
          }
          FUN_00574730();
          if (*local_78 != '\0') {
            if ((*(short *)(local_7c + 0x28) != 0) && (0 < *(int *)(local_7c + 0x80))) {
              if (&stack0x00000000 == (undefined1 *)0x1c0) {
                local_ac = (undefined1 *)0x0;
              }
              else {
                local_ac = auStack_1b0;
              }
              iVar3 = *(int *)(local_7c + 0x80);
              uVar4 = (uint)*(ushort *)(local_7c + 0x28);
              puStack_1ec = &DAT_00884900;
              puStack_1f0 = local_ac;
              pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
              puStack_1ec = (undefined *)0x7a8ece;
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar4);
              puStack_1ec = (undefined *)0x7a8ed4;
              pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650();
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,iVar3);
              FUN_004bc590();
            }
            if (0 < *(int *)(local_7c + 0x84)) {
              if (&stack0x00000000 == (undefined1 *)0x1c0) {
                local_9c = (undefined1 *)0x0;
              }
              else {
                local_9c = auStack_1b0;
              }
              iVar3 = *(int *)(local_7c + 0x88);
              iVar9 = *(int *)(local_7c + 0x84);
              puStack_1ec = &DAT_0089f104;
              puStack_1f0 = local_9c;
              pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
              puStack_1ec = (undefined *)0x7a8f50;
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,iVar9);
              puStack_1ec = (undefined *)0x7a8f56;
              pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650();
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,iVar3);
              FUN_004bc590();
            }
          }
          local_c4 = 0.0;
          local_98 = 0;
          while( true ) {
            local_e8 = GetPolicy();
            local_8._0_1_ = 2;
            local_e0 = local_e8;
            FUN_0041f870();
            fVar7 = (float10)FUN_00689cb0();
            local_f0 = (float)fVar7;
            local_ec = local_f0;
            fVar7 = (float10)FUN_007ca700();
            local_d8 = (float)fVar7;
            local_94 = local_ec * local_d8;
            local_100 = (double)local_94;
            fVar7 = (float10)FUN_007d3ec0();
            local_110 = (double)fVar7;
            local_82 = local_100 < local_110 * 0.62;
            local_bc = (uint)(byte)local_82;
            local_8._0_1_ = 1;
            ~basic_string<>();
            if (((local_82 == '\0') || (local_94 <= local_c4)) ||
               (local_98 = local_98 + 1, 200 < local_98)) break;
            local_c4 = local_94;
            if (&stack0x00000000 == (undefined1 *)0x1c0) {
              local_c0 = (undefined1 *)0x0;
            }
            else {
              local_c0 = auStack_1b0;
            }
            FUN_004bc590();
          }
          if (&stack0x00000000 == (undefined1 *)0x1c0) {
            local_a8 = (undefined1 *)0x0;
          }
          else {
            local_a8 = auStack_1b0;
          }
          local_f4 = (undefined1 *)&puStack_1f0;
          local_104 = std::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  *)&puStack_1f0,
                                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  *)(local_7c + 0x48));
          local_8._0_1_ = 3;
          puVar8 = local_74;
          local_d4 = local_104;
          FUN_00764780(puVar8);
          local_8._0_1_ = 1;
          local_e4 = FUN_00766560(puVar8);
          local_8._0_1_ = 4;
          local_dc = local_e4;
          FUN_00574730();
          local_8 = CONCAT31(local_8._1_3_,1);
          ~basic_string<>();
          FUN_007c48b0();
          iVar3 = FUN_007c48b0();
          uVar6 = local_80 - iVar3;
          uVar4 = FUN_007cb5a0();
          if (uVar6 < uVar4) {
            if (*(char *)(local_7c + 0x60) == '\0') {
              FUN_007c48b0();
              puVar2 = (undefined4 *)FUN_004200d0();
              local_b0 = (int *)*puVar2;
              (**(code **)(*local_b0 + 0x24))();
            }
            else {
              FUN_007c48b0();
              puVar2 = (undefined4 *)FUN_004200d0();
              local_b8 = (int *)*puVar2;
              (**(code **)(*local_b8 + 0x24))();
            }
          }
          local_d0 = GetPolicy();
          local_8._0_1_ = 5;
          local_cc = local_d0;
          FUN_0041f870();
          FUN_007cabf0();
          local_8 = CONCAT31(local_8._1_3_,1);
          ~basic_string<>();
          cVar1 = FUN_0073a900();
          if ((cVar1 != '\0') && (cVar1 = FUN_0056f780(), cVar1 != '\0')) {
            FUN_007cafa0();
            local_81 = '\x01';
          }
          FUN_007c48b0();
          iVar3 = FUN_007c48b0();
          uVar6 = local_80 - iVar3;
          uVar4 = FUN_007cb5a0();
          if (uVar6 < uVar4) {
            FUN_0056f8b0();
            cVar1 = FUN_0056f780();
            if (cVar1 != '\0') {
              puVar2 = (undefined4 *)FUN_004200d0();
              local_a0 = (int *)*puVar2;
              (**(code **)(*local_a0 + 0x24))();
            }
            if (*(char *)(local_7c + 0x44) == '\x01') {
              puVar2 = (undefined4 *)FUN_004200d0();
              local_a4 = (int *)*puVar2;
              (**(code **)(*local_a4 + 0x24))();
            }
          }
          local_80 = local_80 + 1;
          FUN_0042da80();
          local_8 = local_8 & 0xffffff00;
          ~basic_string<>();
          local_8 = 0xffffffff;
          FUN_00417f10();
        }
        if ((local_81 == '\0') && (cVar1 = FUN_0073a900(), cVar1 != '\0')) {
          FUN_0056f7e0();
        }
      }
    }
    FUN_0042da80();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

