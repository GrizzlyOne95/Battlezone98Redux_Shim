
void FUN_00727920(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  undefined4 uStack_288;
  undefined *puStack_284;
  undefined4 uStack_280;
  undefined *puStack_27c;
  undefined4 uStack_278;
  undefined *puStack_274;
  undefined1 auStack_250 [160];
  undefined1 *local_1b0;
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
  undefined4 local_160;
  undefined1 *local_15c;
  undefined4 local_158;
  int local_154;
  uint local_150;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_11c [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_ec [48];
  undefined1 local_bc [144];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859361;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_150 = 0;
  FUN_00574400();
  local_8 = 0;
  cVar1 = FUN_00720f90();
  if (cVar1 == '\0') {
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      local_1a4 = basic_string<>();
      local_8 = 2;
      local_150 = local_150 | 2;
      local_18c = local_1a4;
      local_160 = local_1a4;
    }
    else {
      FUN_00421ec0();
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_006b6010();
      local_1a8 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            (local_11c,pbVar2);
      local_8 = CONCAT31(local_8._1_3_,1);
      local_150 = local_150 | 1;
      local_180 = local_1a8;
      local_160 = local_1a8;
    }
    local_190 = local_160;
    basic_string<>();
    local_8 = 3;
    FUN_006b7490();
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      basic_string<>();
      local_8 = 5;
      local_150 = local_150 | 8;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_006b7490();
      local_17c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            (local_ec,pbVar2);
      local_8 = 6;
      local_150 = local_150 | 0x10;
      local_174 = local_17c;
      local_158 = local_17c;
    }
    else {
      local_19c = basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,4);
      local_150 = local_150 | 4;
      local_170 = local_19c;
      local_158 = local_19c;
    }
    local_1a0 = local_158;
    if (&stack0x00000000 == (undefined1 *)0x260) {
      local_168 = (undefined1 *)0x0;
    }
    else {
      local_168 = auStack_250;
    }
    local_198 = FUN_006d7550();
    local_8 = 7;
    local_188 = local_198;
    FUN_006b73e0();
    uVar3 = FUN_004170c0();
    iVar4 = FUN_006b8f30();
    puStack_274 = &DAT_00899210;
    uStack_278 = 0x727c11;
    uStack_278 = std::allocator<char>::allocator<char>((allocator<char> *)(local_154 + 0x4abc));
    puStack_27c = &DAT_0088d764;
    uStack_280 = local_190;
    puStack_284 = &DAT_0088d764;
    uStack_288 = 0x727c34;
    uStack_288 = FUN_006b81b0();
    uVar5 = FUN_00574730(local_168,local_1a0,&DAT_0088d764,local_198,&DAT_0089921c);
    uVar5 = FUN_004bc590(uVar5);
    uVar5 = FUN_00574730(uVar5);
    uVar5 = FUN_004bc590(uVar5);
    uStack_288 = FUN_00574730(uVar5);
    puStack_284 = (undefined *)FUN_004bc590();
    uStack_288 = 0x727c8f;
    uStack_280 = FUN_00574730();
    puStack_284 = (undefined *)0x727c98;
    puStack_27c = (undefined *)FUN_004bc590();
    uStack_280 = 0x727ca1;
    uStack_278 = FUN_00574730();
    puStack_27c = (undefined *)0x727caa;
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    puStack_274 = (undefined *)0x727cb5;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,iVar4);
    puStack_274 = (undefined *)0x727cbb;
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar3);
    local_8 = CONCAT31(local_8._1_3_,6);
    ~basic_string<>();
    local_8 = 5;
    if ((local_150 & 0x10) != 0) {
      local_150 = local_150 & 0xffffffef;
      ~basic_string<>();
    }
    local_8 = 4;
    if ((local_150 & 8) != 0) {
      local_150 = local_150 & 0xfffffff7;
      ~basic_string<>();
    }
    local_8 = 3;
    if ((local_150 & 4) != 0) {
      local_150 = local_150 & 0xfffffffb;
      ~basic_string<>();
    }
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
    local_8 = 1;
    if ((local_150 & 2) != 0) {
      local_150 = local_150 & 0xfffffffd;
      ~basic_string<>();
    }
    local_8 = 0;
    if ((local_150 & 1) != 0) {
      local_150 = local_150 & 0xfffffffe;
      ~basic_string<>();
    }
    basic_string<>();
    local_8._0_1_ = 8;
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006b7490();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
    local_8._0_1_ = 10;
    ~basic_string<>();
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      basic_string<>();
      local_8._0_1_ = 0xb;
      basic_string<>();
      local_8._0_1_ = 0xc;
      if (&stack0x00000000 == (undefined1 *)0x260) {
        local_164 = (undefined1 *)0x0;
      }
      else {
        local_164 = auStack_250;
      }
      local_1b0 = (undefined1 *)&uStack_288;
      local_1ac = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              *)&uStack_288,local_2c);
      local_184 = FUN_006b6760(local_bc);
      local_8._0_1_ = 0xd;
      puStack_274 = local_164;
      uStack_278 = 0x727ed1;
      local_16c = local_184;
      FUN_004bc590();
      puStack_274 = (undefined *)0x727eda;
      FUN_00574730();
      FUN_004bc590();
      local_8._0_1_ = 0xc;
      ~basic_string<>();
      local_8._0_1_ = 0xb;
      ~basic_string<>();
      local_8._0_1_ = 10;
      ~basic_string<>();
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x260) {
        local_15c = (undefined1 *)0x0;
      }
      else {
        local_15c = auStack_250;
      }
      FUN_004bc590();
    }
    local_194 = GetPolicy();
    local_8._0_1_ = 0xe;
    local_178 = local_194;
    FUN_006d4480();
    local_8._0_1_ = 10;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    FUN_006d08b0();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

