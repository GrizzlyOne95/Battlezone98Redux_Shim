
void FUN_007a6b70(void)

{
  char cVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  uint uVar7;
  float10 fVar8;
  undefined1 *puVar9;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_518 [4];
  undefined4 uStack_514;
  undefined1 *puStack_510;
  undefined1 *puStack_50c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_508;
  code *pcVar10;
  undefined1 local_4f8 [168];
  undefined1 local_450 [184];
  undefined1 auStack_398 [176];
  undefined1 auStack_2e8 [184];
  undefined1 local_230 [4];
  undefined4 local_22c;
  undefined1 local_228 [4];
  undefined1 local_224 [4];
  undefined1 local_220 [8];
  undefined1 local_218 [4];
  double local_214;
  undefined1 local_20c [4];
  undefined1 local_208 [4];
  undefined1 local_204 [4];
  undefined1 local_200 [4];
  undefined1 local_1fc [4];
  double local_1f8;
  undefined1 local_1f0 [4];
  undefined1 *local_1ec;
  undefined1 local_1e8 [44];
  float local_1bc;
  float local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  float local_178;
  undefined4 local_174;
  undefined4 local_164;
  undefined4 local_160;
  int *local_15c;
  undefined1 *local_158;
  int *local_154;
  int *local_150;
  undefined1 *local_14c;
  int *local_148;
  int local_144;
  int *local_140;
  undefined1 *local_13c;
  int *local_138;
  float local_134;
  uint local_130;
  undefined1 *local_12c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_128;
  uint local_124;
  int local_120;
  float local_11c;
  int local_118;
  uint local_114;
  uint local_10c;
  uint local_108;
  char local_101;
  uint local_100;
  int local_fc;
  int local_f8;
  char local_f3;
  undefined1 local_f2;
  byte local_f1;
  int local_f0;
  undefined1 local_d4 [72];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860670;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d37f0();
  cVar1 = FUN_007d3360();
  if ((cVar1 != '\0') &&
     ((((DAT_009180d7 != '\0' || (DAT_00917f4c != '\0')) || (cVar1 = FUN_00577d50(), cVar1 != '\0'))
      || (iVar4 = FUN_00434160(), iVar4 == 2)))) {
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6c12;
    (**(code **)(**(int **)(local_f0 + 0x14c) + 0x24))();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6c25;
    FUN_007cc5c0();
  }
  local_114 = 0;
  while (uVar5 = size(), local_114 < uVar5) {
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6c71;
    FUN_004200d0();
    FUN_007cb5c0();
    local_114 = local_114 + 1;
  }
  pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x7a6c8a;
  basic_string<>();
  local_8 = 0;
  pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x1;
  puStack_50c = local_8c;
  puStack_510 = (undefined1 *)0x7a6ca7;
  FUN_006ca8e0();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  while( true ) {
    pbStack_508 = local_44;
    puStack_50c = local_450;
    puStack_510 = (undefined1 *)0x7a6cd8;
    local_150 = (int *)FUN_004272a0();
    bVar2 = std::ios_base::operator_bool((ios_base *)((int)local_150 + *(int *)(*local_150 + 4)));
    if (!bVar2) break;
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_230;
    puStack_50c = (undefined1 *)0x7a6d16;
    make_move_iterator<>();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_200;
    puStack_50c = (undefined1 *)0x7a6d26;
    FUN_00770900();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_218;
    puStack_50c = (undefined1 *)0x7a6d3b;
    puVar6 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                       (local_44);
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  *puVar6;
    puStack_50c = local_208;
    puStack_510 = (undefined1 *)0x7a6d4d;
    puVar6 = (undefined4 *)FID_conflict_begin();
    puStack_50c = (undefined1 *)*puVar6;
    puStack_510 = local_220;
    uStack_514 = 0x7a6d5c;
    puVar6 = (undefined4 *)FUN_00770920();
    local_184 = *puVar6;
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6d76;
    puVar6 = (undefined4 *)FID_conflict_begin();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  *puVar6;
    puStack_50c = local_1e8;
    puStack_510 = (undefined1 *)0x7a6d9b;
    local_18c = pbStack_508;
    FUN_0071b880();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6daa;
    FUN_006cae50();
  }
  local_108 = 0;
  while (uVar5 = FUN_0048a830(), local_108 < uVar5) {
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x0;
    puStack_50c = (undefined1 *)local_108;
    puStack_510 = (undefined1 *)0x7a6df3;
    FUN_006cf480();
    puStack_50c = (undefined1 *)0x7a6dfa;
    puStack_50c = (undefined1 *)FUN_0041f870();
    puStack_510 = (undefined1 *)local_108;
    uStack_514 = 0x7a6e13;
    FUN_004200d0();
    puStack_510 = (undefined1 *)0x7a6e1a;
    FUN_007cabf0();
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x1;
    puStack_50c = &DAT_008a1ad8;
    puStack_510 = (undefined1 *)local_108;
    uStack_514 = 0x7a6e3b;
    FUN_004200d0();
    puStack_510 = (undefined1 *)0x7a6e42;
    FUN_007cabf0();
    local_108 = local_108 + 1;
  }
  local_128 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)0x2;
  local_118 = 0;
  do {
    if (DAT_00920178 <= local_118) {
LAB_007a7098:
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a70ab;
      FUN_007cafa0();
      local_f3 = '\0';
      FUN_007cb5c0();
      local_f8 = 0;
      local_100 = 0;
      local_fc = FUN_0056f950();
      while( true ) {
        if (local_fc == 0) {
          while (uVar5 = FUN_007cb5a0(), local_100 < uVar5) {
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a76f5;
            puVar6 = (undefined4 *)FUN_004200d0();
            local_148 = (int *)*puVar6;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a7712;
            (**(code **)(*local_148 + 0x24))();
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)local_100;
            puStack_50c = (undefined1 *)0x7a772a;
            puVar6 = (undefined4 *)FUN_004200d0();
            local_138 = (int *)*puVar6;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x0;
            puStack_50c = (undefined1 *)0x7a7747;
            (**(code **)(*local_138 + 0x24))();
            local_100 = local_100 + 1;
          }
          if (local_f3 == '\0') {
            FUN_0056f7e0();
          }
          if (DAT_00945549 != '\0') {
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x3;
            puStack_50c = (undefined1 *)0x7a7786;
            FUN_00574400();
            local_8._0_1_ = 0xe;
            FUN_007a7bd0();
            local_8._0_1_ = 0xf;
            FUN_007a7bd0();
            local_8._0_1_ = 0x10;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a77b9;
            local_1a0 = FUN_004bb540();
            local_8._0_1_ = 0x11;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a77e1;
            local_188 = local_1a0;
            FID_conflict__String_const_iterator<class_std::_String_val<struct_std::_Simple_types<unsigned_short>_>_>
                      ();
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a77f2;
            local_1b0 = FUN_004bb570();
            local_8._0_1_ = 0x12;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a781a;
            local_190 = local_1b0;
            FID_conflict__String_const_iterator<class_std::_String_val<struct_std::_Simple_types<unsigned_short>_>_>
                      ();
            local_8._0_1_ = 0x11;
            FUN_004bb3b0();
            local_8 = CONCAT31(local_8._1_3_,0x10);
            FUN_004bb3b0();
            while( true ) {
              pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x7a7857;
              cVar1 = FID_conflict_operator__();
              if (cVar1 == '\0') break;
              if (&stack0x00000000 == (undefined1 *)0x3a8) {
                local_158 = (undefined1 *)0x0;
              }
              else {
                local_158 = auStack_398;
              }
              pcVar10 = FUN_004bc8c0;
              pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x7a7893;
              iVar4 = FUN_007a7c40();
              pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(iVar4 + 4);
              puStack_50c = local_158;
              puStack_510 = (undefined1 *)0x7a78a3;
              this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730();
              pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x7a78ae;
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar10);
              FUN_007332d0();
            }
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a78c2;
            local_1a8 = GetPolicy();
            local_8._0_1_ = 0x13;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a78e5;
            local_198 = local_1a8;
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)FUN_0041f870();
            puStack_50c = (undefined1 *)0x7a7905;
            (**(code **)(**(int **)(local_f0 + 0x15c) + 0x3c))();
            local_8._0_1_ = 0x10;
            ~basic_string<>();
            local_8._0_1_ = 0xf;
            FUN_004bb3d0();
            local_8._0_1_ = 0xe;
            FUN_004bb3d0();
            local_8 = CONCAT31(local_8._1_3_,3);
            FUN_00417f10();
          }
          local_8._0_1_ = 2;
          ~basic_string<>();
          local_8._0_1_ = 1;
          FUN_0048a040();
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_006b95c0();
          local_8 = 0xffffffff;
          ~basic_string<>();
          ExceptionList = local_10;
          FUN_0083e885();
          return;
        }
        FUN_00764760();
        local_120 = FUN_0056f900();
        if (local_120 != 0) break;
LAB_007a74fd:
        cVar1 = FUN_0073a900();
        if (cVar1 != '\0') {
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a7530;
          cVar1 = FUN_0056f780();
          if (cVar1 != '\0') {
            pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x7a754f;
            FUN_007cafa0();
            local_f3 = '\x01';
          }
        }
        FUN_007c48b0();
        iVar4 = FUN_007c48b0();
        uVar7 = local_f8 - iVar4;
        uVar5 = FUN_007cb5a0();
        if (uVar7 < uVar5) {
          sVar3 = FUN_007a4790();
          local_f2 = sVar3 == *(short *)(local_fc + 0x28);
          FUN_007c48b0();
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a75f8;
          puVar6 = (undefined4 *)FUN_004200d0();
          local_154 = (int *)*puVar6;
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a761b;
          (**(code **)(*local_154 + 0x24))();
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(uint)*(ushort *)(local_fc + 0x28);
          puStack_50c = (undefined1 *)0x7a762b;
          iVar4 = FUN_00572b50();
          local_f1 = iVar4 != 0;
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a7653;
          iVar4 = FUN_007c48b0();
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(local_f8 - iVar4);
          puStack_50c = (undefined1 *)0x7a766d;
          puVar6 = (undefined4 *)FUN_004200d0();
          local_15c = (int *)*puVar6;
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(uint)local_f1;
          puStack_50c = (undefined1 *)0x7a7690;
          (**(code **)(*local_15c + 0x24))();
          local_100 = local_100 + 1;
        }
        local_f8 = local_f8 + 1;
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x7a70f0;
        local_fc = FUN_00577b50();
      }
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a713d;
      FUN_0042d8c0();
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a7155;
      FID_conflict_begin();
LAB_007a7155:
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a7167;
      cVar1 = FUN_00420f10();
      if (cVar1 != '\0') {
        sVar3 = FUN_0056f920();
        iVar4 = FUN_0042da60();
        if (sVar3 != *(short *)(iVar4 + 0x28)) break;
        local_144 = FUN_0042de50();
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x3;
        puStack_50c = (undefined1 *)0x7a71b7;
        FUN_00574400();
        local_8._0_1_ = 8;
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x7a71cd;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_5c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(local_144 + 0x2c));
        local_8._0_1_ = 9;
        uVar5 = FUN_004170c0();
        if (0x15 < uVar5) {
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a71e8;
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                    (local_5c,0x15);
        }
        if (&stack0x00000000 == (undefined1 *)0x2f8) {
          local_12c = (undefined1 *)0x0;
        }
        else {
          local_12c = auStack_2e8;
        }
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_12c;
        puStack_50c = (undefined1 *)0x7a721d;
        FUN_00574730();
        local_134 = 0.0;
        local_124 = 0;
        while( true ) {
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x7a724c;
          local_1b4 = GetPolicy();
          local_8._0_1_ = 10;
          local_1ac = local_1b4;
          FUN_0041f870();
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)DAT_0091552c;
          puStack_50c = (undefined1 *)0x7a727a;
          fVar8 = (float10)FUN_00689cb0();
          local_1bc = (float)fVar8;
          local_1b8 = local_1bc;
          fVar8 = (float10)FUN_007ca700();
          local_178 = (float)fVar8;
          local_11c = local_1b8 * local_178;
          local_214 = (double)local_11c;
          fVar8 = (float10)FUN_007d3ec0();
          local_1f8 = (double)fVar8;
          local_101 = local_214 < local_1f8 * 0.6;
          local_130 = (uint)(byte)local_101;
          local_8._0_1_ = 9;
          ~basic_string<>();
          if (((local_101 == '\0') || (local_11c <= local_134)) ||
             (local_124 = local_124 + 1, 200 < local_124)) break;
          local_134 = local_11c;
          if (&stack0x00000000 == (undefined1 *)0x2f8) {
            local_13c = (undefined1 *)0x0;
          }
          else {
            local_13c = auStack_2e8;
          }
          pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)local_13c;
          puStack_50c = (undefined1 *)0x7a73bd;
          FUN_004bc590();
        }
        if (&stack0x00000000 == (undefined1 *)0x2f8) {
          local_14c = (undefined1 *)0x0;
        }
        else {
          local_14c = auStack_2e8;
        }
        local_1ec = abStack_518;
        local_22c = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              (abStack_518,
                               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(local_144 + 0x48));
        local_8._0_1_ = 0xb;
        puVar9 = local_d4;
        local_164 = local_22c;
        FUN_00764780(puVar9);
        local_8._0_1_ = 9;
        local_17c = FUN_00766560(puVar9);
        local_8._0_1_ = 0xc;
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_14c;
        puStack_50c = (undefined1 *)0x7a745c;
        local_174 = local_17c;
        FUN_00574730();
        local_8._0_1_ = 9;
        ~basic_string<>();
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x7a7480;
        local_180 = GetPolicy();
        local_8._0_1_ = 0xd;
        pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_f8;
        puStack_50c = (undefined1 *)0x7a74af;
        local_160 = local_180;
        puStack_50c = (undefined1 *)FUN_0041f870();
        puStack_510 = (undefined1 *)0x7a74c1;
        FUN_007cabf0();
        local_8._0_1_ = 9;
        ~basic_string<>();
        local_8._0_1_ = 8;
        ~basic_string<>();
        local_8 = CONCAT31(local_8._1_3_,3);
        FUN_00417f10();
      }
      goto LAB_007a74fd;
    }
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7a6e94;
    basic_string<>();
    local_8._0_1_ = 4;
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_74;
    puStack_50c = (undefined1 *)0x7a6ea6;
    cVar1 = FUN_00427270();
    if (cVar1 != '\0') {
      local_8 = CONCAT31(local_8._1_3_,3);
      ~basic_string<>();
      goto LAB_007a7098;
    }
    pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x1;
    puStack_50c = local_74;
    puStack_510 = (undefined1 *)0x7a6ed4;
    FUN_006ca8e0();
    local_8._0_1_ = 5;
    vector<>();
    local_8._0_1_ = 6;
    basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,7);
    while( true ) {
      pbStack_508 = local_2c;
      puStack_50c = local_4f8;
      puStack_510 = (undefined1 *)0x7a6f05;
      local_140 = (int *)FUN_004272a0();
      bVar2 = std::ios_base::operator_bool((ios_base *)((int)local_140 + *(int *)(*local_140 + 4)));
      if (!bVar2) break;
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_1f0;
      puStack_50c = (undefined1 *)0x7a6f43;
      make_move_iterator<>();
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_1fc;
      puStack_50c = (undefined1 *)0x7a6f53;
      FUN_00770900();
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    local_204;
      puStack_50c = (undefined1 *)0x7a6f68;
      puVar6 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               end(local_2c);
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    *puVar6;
      puStack_50c = local_20c;
      puStack_510 = (undefined1 *)0x7a6f7a;
      puVar6 = (undefined4 *)FID_conflict_begin();
      puStack_50c = (undefined1 *)*puVar6;
      puStack_510 = local_228;
      uStack_514 = 0x7a6f89;
      puVar6 = (undefined4 *)FUN_00770920();
      local_194 = *puVar6;
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a6fa3;
      puVar6 = (undefined4 *)FID_conflict_begin();
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    *puVar6;
      puStack_50c = local_224;
      puStack_510 = (undefined1 *)0x7a6fc8;
      local_19c = pbStack_508;
      FUN_0071b880();
      pbStack_508 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x7a6fd7;
      FUN_006cae50();
    }
    local_10c = 0;
    while (uVar5 = FUN_0048a830(), local_10c < uVar5) {
      pbStack_508 = local_128;
      puStack_50c = (undefined1 *)local_10c;
      puStack_510 = (undefined1 *)0x7a7025;
      FUN_006cf480();
      puStack_50c = (undefined1 *)0x7a702c;
      puStack_50c = (undefined1 *)FUN_0041f870();
      puStack_510 = (undefined1 *)local_10c;
      uStack_514 = 0x7a7045;
      FUN_004200d0();
      puStack_510 = (undefined1 *)0x7a704c;
      FUN_007cabf0();
      local_10c = local_10c + 1;
    }
    local_128 = local_128 + 1;
    local_8._0_1_ = 6;
    ~basic_string<>();
    local_8._0_1_ = 5;
    FUN_0048a040();
    local_8._0_1_ = 4;
    FUN_006b95c0();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
    local_118 = local_118 + 1;
  } while( true );
  FUN_0042da80();
  goto LAB_007a7155;
}

