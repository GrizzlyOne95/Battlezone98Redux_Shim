
void __fastcall FUN_007ccfc0(int *param_1)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  float10 fVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  undefined1 local_24c [176];
  undefined1 local_19c [4];
  undefined1 local_198 [4];
  undefined4 local_194;
  undefined8 local_190;
  undefined4 local_188;
  float local_184;
  undefined4 local_180;
  undefined4 local_17c;
  int local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  int local_168;
  float local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  int local_150;
  uint local_14c;
  int *local_148;
  undefined8 local_144;
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  int local_120;
  int *local_11c;
  char local_115;
  int local_114;
  char local_10d;
  int local_10c;
  int *local_108;
  undefined1 local_104 [24];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_74 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862652;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_108 = param_1;
  if (param_1[0xa52] != 0) {
    FUN_00688110(param_1[0xa52],local_14);
    local_108[0xa52] = 0;
  }
  local_190 = CONCAT44(local_190._4_4_,(undefined4)local_190);
  local_144 = CONCAT44(local_144._4_4_,(undefined4)local_144);
  if (local_108 != (int *)0xfffffebc) {
    local_11c = local_108 + 0x51;
    local_178 = (int)local_108 + 0x145;
    do {
      local_10d = (char)*local_11c;
      local_11c = (int *)((int)local_11c + 1);
    } while (local_10d != '\0');
    local_168 = (int)local_11c - local_178;
    local_190 = CONCAT44(local_190._4_4_,(undefined4)local_190);
    local_144 = CONCAT44(local_144._4_4_,(undefined4)local_144);
    if (local_168 != 0) {
      local_174 = fegetround();
      fesetround(0x100);
      local_150 = (int)(float)local_108[1];
      local_134 = (int)(float)local_108[2];
      fesetround(0x200);
      local_13c = (int)((float)local_108[1] + (float)local_108[3]) - local_150;
      local_138 = (int)((float)local_108[2] + (float)local_108[4]) - local_134;
      fesetround(local_174);
      basic_string<>(local_108 + 0x51);
      local_8 = 0;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
                (local_74,0,2);
      FUN_004203f0(local_74,3,1);
      local_8._0_1_ = 1;
      basic_string<>();
      local_8._0_1_ = 2;
      vector<>();
      local_8 = CONCAT31(local_8._1_3_,3);
      while( true ) {
        local_148 = (int *)FUN_004272a0(local_24c,local_8c,10);
        bVar1 = std::ios_base::operator_bool
                          ((ios_base *)((int)local_148 + *(int *)(*local_148 + 4)));
        if (!bVar1) break;
        FUN_006cae50(local_8c);
      }
      local_190 = FUN_00689eb0();
      local_144 = local_190;
      FUN_00689ec0((float)local_190 * (float)local_108[0xa51],
                   (float)((ulonglong)local_190 >> 0x20) * (float)local_108[0xa51]);
      local_10c = 0;
      while( true ) {
        iVar3 = FUN_0048a830();
        if (local_10c == iVar3) break;
        FUN_006cf480(local_10c);
        uVar4 = FUN_0041f870();
        fVar6 = (float10)FUN_00689cb0(DAT_0091552c,uVar4);
        local_184 = (float)fVar6;
        if ((float)local_13c < local_184) {
          local_114 = 0;
          pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_006cf480(local_10c);
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                    (local_2c,pbVar5);
          local_8._0_1_ = 4;
          while( true ) {
            local_15c = FUN_0045e1d0(local_104,0,local_114);
            local_8._0_1_ = 5;
            local_158 = local_15c;
            uVar4 = FUN_0041f870();
            fVar6 = (float10)FUN_00689cb0(DAT_0091552c,uVar4);
            local_164 = (float)fVar6;
            local_115 = local_164 < (float)local_108[3];
            local_14c = (uint)(byte)local_115;
            local_8._0_1_ = 4;
            ~basic_string<>();
            if (local_115 == '\0') break;
            local_114 = local_114 + 1;
          }
          if (0 < local_114) {
            uVar4 = 0;
            puVar7 = local_44;
            iVar3 = local_114;
            FUN_006cf480(local_10c);
            FUN_0045e1d0(puVar7,uVar4,iVar3);
            local_8._0_1_ = 6;
            local_130 = FUN_00489f20(&DAT_0088d764,0xffffffff);
            if (local_130 == -1) {
              local_188 = FUN_0045e1d0(local_bc,0,local_114);
              FUN_0045e0f0(local_188);
              ~basic_string<>();
              uVar4 = FUN_0045e1d0(local_ec,local_114,0xffffffff);
              local_8._0_1_ = 8;
              local_194 = uVar4;
              local_16c = uVar4;
              FUN_006cf480(local_10c);
              FUN_0045e0f0(uVar4);
              local_8 = CONCAT31(local_8._1_3_,6);
              ~basic_string<>();
            }
            else {
              local_170 = FUN_0045e1d0(local_d4,0,local_130);
              FUN_0045e0f0(local_170);
              ~basic_string<>();
              uVar4 = FUN_0045e1d0(local_a4,local_130 + 1,0xffffffff);
              local_8._0_1_ = 7;
              local_180 = uVar4;
              local_154 = uVar4;
              FUN_006cf480(local_10c);
              FUN_0045e0f0(uVar4);
              local_8 = CONCAT31(local_8._1_3_,6);
              ~basic_string<>();
            }
            puVar8 = &local_17c;
            iVar3 = local_10c;
            FID_conflict_begin(local_19c);
            FID_conflict_operator_(puVar8,iVar3);
            local_160 = local_17c;
            FUN_007ceb90(local_198,local_17c,local_44);
            local_8._0_1_ = 4;
            ~basic_string<>();
          }
          local_8 = CONCAT31(local_8._1_3_,3);
          ~basic_string<>();
        }
        local_10c = local_10c + 1;
      }
      basic_string<>(&DAT_008a1ad8);
      local_8._0_1_ = 9;
      local_120 = 0;
      while( true ) {
        iVar3 = FUN_0048a830();
        if (local_120 == iVar3) break;
        uVar4 = FUN_006cf480(local_120);
        FUN_00449810(uVar4);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_5c,"\n");
        local_120 = local_120 + 1;
      }
      (**(code **)(*local_108 + 0x40))(local_138,local_5c);
      FUN_00689ec0(local_144);
      uVar2 = FUN_007d3ee0();
      uVar4 = FUN_0041f870(local_108[0xa51],local_108[0x40],uVar2);
      iVar3 = FUN_00688130(local_150,local_134,local_13c,local_138,uVar4);
      local_108[0xa52] = iVar3;
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      FUN_0048a040();
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

