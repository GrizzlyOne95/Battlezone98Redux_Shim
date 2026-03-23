
void __thiscall FUN_007458a0(int *param_1,undefined4 param_2)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  uint uVar2;
  undefined4 uStack_2b0;
  undefined1 *puStack_2ac;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_2a8;
  char *pcStack_2a4;
  undefined *puStack_2a0;
  code *pcVar3;
  undefined1 local_290 [48];
  undefined1 auStack_260 [160];
  undefined1 *local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
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
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined1 *local_168;
  undefined1 *local_164;
  undefined1 *local_160;
  undefined1 *local_15c;
  undefined1 *local_158;
  undefined1 local_153;
  undefined1 local_152;
  undefined1 local_151;
  int *local_150;
  undefined1 local_134 [48];
  undefined1 local_104 [24];
  undefined1 local_ec [72];
  undefined1 local_a4 [24];
  undefined1 local_8c [48];
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b68b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_150 = param_1;
  local_153 = (**(code **)(*param_1 + 0x58))();
  local_151 = 0;
  puStack_2a0 = (undefined *)0x0;
  pcStack_2a4 = local_2c;
  pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x745905;
  FUN_0045e1d0();
  local_8._1_3_ = 0;
  if ((DAT_02cc37ac & 1) == 0) {
    DAT_02cc37ac = DAT_02cc37ac | 1;
    local_8._0_1_ = 1;
    local_8._1_3_ = 0;
    puStack_2a0 = (undefined *)0x74593b;
    puStack_2a0 = (undefined *)basic_string<>();
    local_8._0_1_ = 2;
    pcStack_2a4 = local_ec;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745969;
    local_1b4 = puStack_2a0;
    local_19c = puStack_2a0;
    puStack_2a0 = (undefined *)FUN_0045f170();
    local_8._0_1_ = 3;
    pcStack_2a4 = &DAT_02cc37b4;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745999;
    local_174 = puStack_2a0;
    local_170 = puStack_2a0;
    FUN_0045f170();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    puStack_2a0 = (undefined *)0x7459c1;
    FUN_0083e979();
  }
  if ((DAT_02cc37ac & 2) == 0) {
    DAT_02cc37ac = DAT_02cc37ac | 2;
    local_8._0_1_ = 4;
    puStack_2a0 = (undefined *)0x7459fa;
    puStack_2a0 = (undefined *)basic_string<>();
    local_8._0_1_ = 5;
    pcStack_2a4 = local_8c;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745a28;
    local_184 = puStack_2a0;
    local_17c = puStack_2a0;
    puStack_2a0 = (undefined *)FUN_0045f170();
    local_8._0_1_ = 6;
    pcStack_2a4 = &DAT_02cc3844;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745a58;
    local_190 = puStack_2a0;
    local_18c = puStack_2a0;
    FUN_0045f170();
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 4;
    ~basic_string<>();
    puStack_2a0 = (undefined *)0x745a83;
    FUN_0083e979();
  }
  if ((DAT_02cc37ac & 4) == 0) {
    DAT_02cc37ac = DAT_02cc37ac | 4;
    local_8._0_1_ = 7;
    puStack_2a0 = (undefined *)0x745abc;
    puStack_2a0 = (undefined *)basic_string<>();
    local_8._0_1_ = 8;
    pcStack_2a4 = local_104;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745aea;
    local_1a0 = puStack_2a0;
    local_198 = puStack_2a0;
    puStack_2a0 = (undefined *)FUN_0045f170();
    local_8._0_1_ = 9;
    pcStack_2a4 = &DAT_02cc37cc;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745b1a;
    local_1b0 = puStack_2a0;
    local_1a8 = puStack_2a0;
    FUN_0045f170();
    local_8._0_1_ = 8;
    ~basic_string<>();
    local_8._0_1_ = 7;
    ~basic_string<>();
    puStack_2a0 = (undefined *)0x745b45;
    FUN_0083e979();
  }
  if ((DAT_02cc37ac & 8) == 0) {
    DAT_02cc37ac = DAT_02cc37ac | 8;
    local_8._0_1_ = 10;
    puStack_2a0 = (undefined *)0x745b7e;
    puStack_2a0 = (undefined *)basic_string<>();
    local_8._0_1_ = 0xb;
    pcStack_2a4 = local_134;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745bac;
    local_1b8 = puStack_2a0;
    local_194 = puStack_2a0;
    puStack_2a0 = (undefined *)FUN_0045f170();
    local_8._0_1_ = 0xc;
    pcStack_2a4 = &DAT_02cc38c4;
    pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x745bdc;
    local_178 = puStack_2a0;
    local_16c = puStack_2a0;
    FUN_0045f170();
    local_8._0_1_ = 0xb;
    ~basic_string<>();
    local_8._0_1_ = 10;
    ~basic_string<>();
    puStack_2a0 = (undefined *)0x745c07;
    FUN_0083e979();
  }
  local_8._0_1_ = 0;
  pcVar3 = FUN_004bc8c0;
  puStack_2a0 = (undefined *)param_2;
  pcStack_2a4 = "Sending ";
  pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x745c21;
  FUN_0081e820();
  pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x745c28;
  pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                FUN_0081e660();
  puStack_2ac = (undefined1 *)0x745c2e;
  pcStack_2a4 = (char *)FUN_004bc590();
  pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                0x745c37;
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730();
  puStack_2a0 = (undefined *)0x745c42;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar3);
  puStack_2a0 = local_2c;
  pcStack_2a4 = (undefined1 *)0x745c50;
  cVar1 = operator!=<>();
  if (cVar1 != '\0') {
    puStack_2a0 = local_2c;
    pcStack_2a4 = (undefined1 *)0x745c6c;
    cVar1 = operator!=<>();
    if (cVar1 != '\0') {
      puStack_2a0 = local_2c;
      pcStack_2a4 = (undefined1 *)0x745c88;
      cVar1 = operator!=<>();
      if (cVar1 != '\0') {
        puStack_2a0 = local_2c;
        pcStack_2a4 = (undefined1 *)0x745ca4;
        cVar1 = operator!=<>();
        if (cVar1 != '\0') {
          puStack_2a0 = (undefined *)0x3;
          pcStack_2a4 = (char *)0x745cc1;
          FUN_00574400();
          local_8._0_1_ = 0xd;
          puStack_2a0 = (undefined *)0x745cdf;
          puStack_2a0 = (undefined *)(**(code **)(*local_150 + 0x38))();
          pcStack_2a4 = local_5c;
          pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x745cf7;
          (**(code **)(*local_150 + 0x50))();
          local_8 = CONCAT31(local_8._1_3_,0xe);
          pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x745d03;
          cVar1 = FUN_0041f890();
          if (cVar1 == '\0') {
            if (&stack0x00000000 == (undefined1 *)0x270) {
              local_168 = (undefined1 *)0x0;
            }
            else {
              local_168 = auStack_260;
            }
            pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)local_5c;
            puStack_2ac = local_168;
            uStack_2b0 = 0x745d3f;
            FUN_00574730();
          }
          else {
            if (&stack0x00000000 == (undefined1 *)0x270) {
              local_164 = (undefined1 *)0x0;
            }
            else {
              local_164 = auStack_260;
            }
            pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)local_290;
            puStack_2ac = (undefined1 *)0x745d83;
            pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(**(code **)(*local_150 + 0x38))();
            puStack_2ac = local_164;
            uStack_2b0 = 0x745d90;
            FUN_0073ba70();
          }
          if (&stack0x00000000 == (undefined1 *)0x270) {
            local_158 = (undefined1 *)0x0;
          }
          else {
            local_158 = auStack_260;
          }
          pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_00874924;
          puStack_2ac = local_158;
          uStack_2b0 = 0x745dc9;
          FUN_004bc590();
          if (&stack0x00000000 == (undefined1 *)0x270) {
            local_15c = (undefined1 *)0x0;
          }
          else {
            local_15c = auStack_260;
          }
          pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)param_2;
          puStack_2ac = local_15c;
          uStack_2b0 = 0x745e01;
          FUN_00574730();
          pbStack_2a8 = local_44;
          puStack_2ac = (undefined1 *)0x745e13;
          GetPolicy();
          local_8._0_1_ = 0xf;
          if (&stack0x00000000 == (undefined1 *)0x270) {
            local_160 = (undefined1 *)0x0;
          }
          else {
            local_160 = auStack_260;
          }
          pbStack_2a8 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)&DAT_0087a44c;
          puStack_2ac = local_160;
          uStack_2b0 = 0x745e4d;
          FUN_004bc590();
          puStack_2a0 = (undefined *)0x745e62;
          local_1ac = GetPolicy();
          local_8._0_1_ = 0x10;
          puStack_2a0 = (undefined *)0x745e84;
          local_180 = local_1ac;
          FUN_0081e8a0();
          puStack_2a0 = (undefined *)0x745e8b;
          FUN_0081e6c0();
          local_8 = CONCAT31(local_8._1_3_,0xf);
          ~basic_string<>();
          if ((char)local_150[0x30] == '\x01') {
            local_1c0 = (undefined1 *)&uStack_2b0;
            local_1bc = std::
                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        ::
                        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                    *)&uStack_2b0,local_44);
            local_1a4 = FUN_0073bdb0(local_a4);
            puStack_2a0 = (undefined *)0x745ef6;
            local_188 = local_1a4;
            FUN_0045e0f0();
            ~basic_string<>();
          }
          puStack_2a0 = (undefined *)0x745f13;
          FUN_00747e10();
          uVar2 = FUN_004170c0();
          if (1000 < uVar2) {
            FUN_00747f30();
          }
          local_151 = 1;
          local_8._0_1_ = 0xe;
          ~basic_string<>();
          local_8._0_1_ = 0xd;
          ~basic_string<>();
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_00417f10();
        }
      }
    }
  }
  local_152 = local_151;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

