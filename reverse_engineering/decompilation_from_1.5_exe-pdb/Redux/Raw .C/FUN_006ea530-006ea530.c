
void FUN_006ea530(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_24c [12];
  undefined4 uStack_240;
  undefined1 *puStack_23c;
  undefined1 *puStack_238;
  undefined1 *puStack_234;
  undefined1 *puStack_230;
  undefined1 auStack_214 [160];
  undefined4 local_174;
  undefined1 *local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined1 *local_138;
  undefined1 *local_134;
  undefined1 *local_130;
  int local_12c;
  undefined1 *local_128;
  undefined1 *local_124;
  undefined4 local_120;
  undefined1 *local_11c;
  undefined1 *local_118;
  undefined1 *local_114;
  undefined1 *local_110;
  int local_10c;
  uint local_108;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_ec [24];
  undefined1 local_d4 [96];
  undefined1 local_74 [24];
  undefined1 local_5c [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854b7b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_108 = 0;
  puStack_230 = (undefined1 *)0x3;
  puStack_234 = (undefined1 *)0x6ea57a;
  FUN_00574400();
  local_8 = 0;
  puStack_230 = (undefined1 *)0x6ea592;
  local_12c = FUN_006f91f0();
  if (&stack0x00000000 == (undefined1 *)0x224) {
    local_130 = (undefined1 *)0x0;
  }
  else {
    local_130 = auStack_214;
  }
  puStack_230 = local_130;
  puStack_234 = (undefined1 *)0x6ea5d1;
  FUN_004bc590();
  if (&stack0x00000000 == (undefined1 *)0x224) {
    local_134 = (undefined1 *)0x0;
  }
  else {
    local_134 = auStack_214;
  }
  puStack_230 = (undefined1 *)0x6ea60b;
  local_160 = FUN_006d7550();
  local_8._0_1_ = 1;
  puStack_230 = local_134;
  puStack_234 = (undefined1 *)0x6ea634;
  local_154 = local_160;
  FUN_00574730();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  if (local_12c < 0) {
    if (&stack0x00000000 == (undefined1 *)0x224) {
      local_11c = (undefined1 *)0x0;
    }
    else {
      local_11c = auStack_214;
    }
    puStack_230 = local_11c;
    puStack_234 = (undefined1 *)0x6ea685;
    FUN_004bc590();
  }
  else {
    if (&stack0x00000000 == (undefined1 *)0x224) {
      local_124 = (undefined1 *)0x0;
    }
    else {
      local_124 = auStack_214;
    }
    puStack_230 = &DAT_00879814;
    puStack_234 = local_124;
    puStack_238 = (undefined1 *)0x6ea6c7;
    iVar3 = local_12c;
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    puStack_230 = (undefined1 *)0x6ea6d2;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,iVar3);
  }
  puStack_230 = (undefined1 *)0x6ea6df;
  basic_string<>();
  local_8._0_1_ = 2;
  puStack_230 = (undefined1 *)0x6ea6f8;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006b7490();
  puStack_230 = (undefined1 *)0x6ea701;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
  local_8._0_1_ = 4;
  ~basic_string<>();
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    puStack_230 = (undefined1 *)0x6ea767;
    basic_string<>();
    local_8._0_1_ = 5;
    puStack_230 = (undefined1 *)0x6ea778;
    basic_string<>();
    local_8._0_1_ = 6;
    if (&stack0x00000000 == (undefined1 *)0x224) {
      local_118 = (undefined1 *)0x0;
    }
    else {
      local_118 = auStack_214;
    }
    puStack_230 = local_74;
    puStack_234 = local_5c;
    local_170 = abStack_24c;
    local_174 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          (abStack_24c,local_2c);
    puStack_230 = (undefined1 *)FUN_006b6760(local_d4);
    local_8._0_1_ = 7;
    puStack_234 = &DAT_0089921c;
    puStack_238 = local_118;
    puStack_23c = (undefined1 *)0x6ea805;
    local_168 = puStack_230;
    local_158 = puStack_230;
    puStack_234 = (undefined1 *)FUN_004bc590();
    puStack_238 = (undefined1 *)0x6ea80e;
    puStack_230 = (undefined1 *)FUN_00574730();
    puStack_234 = (undefined1 *)0x6ea817;
    FUN_004bc590();
    local_8._0_1_ = 6;
    ~basic_string<>();
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 4;
    ~basic_string<>();
  }
  else {
    if (&stack0x00000000 == (undefined1 *)0x224) {
      local_114 = (undefined1 *)0x0;
    }
    else {
      local_114 = auStack_214;
    }
    puStack_230 = local_114;
    puStack_234 = (undefined1 *)0x6ea752;
    FUN_004bc590();
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    puStack_230 = (undefined1 *)0x6ea8c0;
    local_15c = basic_string<>();
    local_8 = 9;
    local_108 = local_108 | 2;
    local_13c = local_15c;
    local_120 = local_15c;
  }
  else {
    FUN_00421ec0();
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006b6010();
    puStack_230 = (undefined1 *)0x6ea87d;
    local_148 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          (local_ec,pbVar2);
    local_8 = CONCAT31(local_8._1_3_,8);
    local_108 = local_108 | 1;
    local_140 = local_148;
    local_120 = local_148;
  }
  local_164 = local_120;
  if (&stack0x00000000 == (undefined1 *)0x224) {
    local_128 = (undefined1 *)0x0;
  }
  else {
    local_128 = auStack_214;
  }
  puStack_230 = local_128;
  puStack_234 = (undefined1 *)0x6ea938;
  FUN_00574730();
  local_8 = 8;
  if ((local_108 & 2) != 0) {
    local_108 = local_108 & 0xfffffffd;
    ~basic_string<>();
  }
  local_8 = 4;
  if ((local_108 & 1) != 0) {
    local_108 = local_108 & 0xfffffffe;
    ~basic_string<>();
  }
  if (&stack0x00000000 == (undefined1 *)0x224) {
    local_110 = (undefined1 *)0x0;
  }
  else {
    local_110 = auStack_214;
  }
  iVar3 = FUN_006b8f30();
  puStack_230 = &DAT_0088d764;
  puStack_234 = local_110;
  puStack_238 = (undefined1 *)0x6ea9cb;
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
  puStack_230 = (undefined1 *)0x6ea9d6;
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,iVar3);
  if (&stack0x00000000 == (undefined1 *)0x224) {
    local_138 = (undefined1 *)0x0;
  }
  else {
    local_138 = auStack_214;
  }
  puStack_230 = (undefined1 *)0x6eaa13;
  local_16c = FUN_006ab780();
  local_8._0_1_ = 10;
  puStack_230 = &DAT_0088d764;
  puStack_234 = (undefined1 *)(local_10c + 0x4c28);
  puStack_238 = &DAT_0088d764;
  puStack_23c = local_138;
  uStack_240 = 0x6eaa53;
  local_150 = local_16c;
  puStack_238 = (undefined1 *)FUN_004bc590();
  puStack_23c = (undefined1 *)0x6eaa5c;
  puStack_234 = (undefined1 *)FUN_006f01a0();
  puStack_238 = (undefined1 *)0x6eaa65;
  puStack_230 = (undefined1 *)FUN_004bc590();
  puStack_234 = (undefined1 *)0x6eaa6e;
  FUN_00574730();
  local_8._0_1_ = 4;
  ~basic_string<>();
  puStack_230 = (undefined1 *)0x6eaa92;
  local_14c = GetPolicy();
  local_8._0_1_ = 0xb;
  puStack_230 = (undefined1 *)0x2000;
  puStack_234 = (undefined1 *)0x6eaac5;
  local_144 = local_14c;
  FUN_006d4480();
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

