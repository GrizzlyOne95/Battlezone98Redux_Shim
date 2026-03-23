
void FUN_00720a50(void)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_224 [16];
  undefined4 uStack_214;
  basic_ostream<char,struct_std::char_traits<char>_> *pbStack_210;
  basic_ostream<char,struct_std::char_traits<char>_> *pbStack_20c;
  basic_ostream<char,struct_std::char_traits<char>_> local_1ec [160];
  undefined1 *local_14c;
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
  basic_ostream<char,struct_std::char_traits<char>_> *local_118;
  basic_ostream<char,struct_std::char_traits<char>_> *local_114;
  basic_ostream<char,struct_std::char_traits<char>_> *local_110;
  basic_ostream<char,struct_std::char_traits<char>_> *local_10c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_108;
  basic_ostream<char,struct_std::char_traits<char>_> *local_104;
  char *local_100;
  undefined4 local_fc;
  int local_f8;
  uint local_f0;
  undefined1 local_d4 [72];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  undefined1 local_74 [72];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858c70;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_f0 = 0;
  pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720a9a;
  FUN_00574400();
  local_8 = 0;
  cVar1 = FUN_00720f90();
  if (cVar1 == '\0') {
    local_f8 = -1;
  }
  else {
    local_f8 = FUN_006f91f0();
  }
  if (local_f8 == -1) {
    local_100 = "HTTP";
  }
  else {
    local_100 = "WebSocket";
  }
  if (&stack0x00000000 == (undefined1 *)0x1fc) {
    local_110 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_110 = local_1ec;
  }
  pbStack_20c = local_110;
  pbStack_210 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720b3f;
  FUN_004bc590();
  pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720b48;
  FUN_004bc590();
  if (&stack0x00000000 == (undefined1 *)0x1fc) {
    local_118 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_118 = local_1ec;
  }
  local_12c = FUN_006d7550();
  local_8._0_1_ = 1;
  pbStack_20c = local_118;
  pbStack_210 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720bb0;
  local_128 = local_12c;
  FUN_00574730();
  pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720bb9;
  FUN_004bc590();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  if (local_f8 != -1) {
    if (&stack0x00000000 == (undefined1 *)0x1fc) {
      local_104 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_104 = local_1ec;
    }
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)&DAT_00895900;
    pbStack_210 = local_104;
    uStack_214 = 0x720c16;
    iVar3 = local_f8;
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720c21;
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,iVar3);
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720c27;
    FUN_004bc590();
  }
  basic_string<>();
  local_8._0_1_ = 2;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006b7490();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
  local_8._0_1_ = 4;
  ~basic_string<>();
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    basic_string<>();
    local_8._0_1_ = 5;
    basic_string<>();
    local_8._0_1_ = 6;
    if (&stack0x00000000 == (undefined1 *)0x1fc) {
      local_10c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_10c = local_1ec;
    }
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)local_74;
    local_14c = abStack_224;
    local_148 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          (abStack_224,local_2c);
    local_140 = FUN_006b6760(local_d4);
    local_8._0_1_ = 7;
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)&DAT_00892bd0;
    pbStack_210 = local_10c;
    uStack_214 = 0x720d5d;
    local_138 = local_140;
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
    pbStack_210 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720d66;
    FUN_00574730();
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720d6f;
    FUN_004bc590();
    local_8._0_1_ = 6;
    ~basic_string<>();
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8._0_1_ = 4;
    ~basic_string<>();
  }
  else {
    if (&stack0x00000000 == (undefined1 *)0x1fc) {
      local_114 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_114 = local_1ec;
    }
    pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720caa;
    FUN_004bc590();
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_13c = basic_string<>();
    local_8 = 9;
    local_f0 = local_f0 | 2;
    local_134 = local_13c;
    local_fc = local_13c;
  }
  else {
    FUN_00421ec0();
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_006b6010();
    local_120 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          (local_8c,pbVar2);
    local_8 = CONCAT31(local_8._1_3_,8);
    local_f0 = local_f0 | 1;
    local_11c = local_120;
    local_fc = local_120;
  }
  local_144 = local_fc;
  if (&stack0x00000000 == (undefined1 *)0x1fc) {
    local_108 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
  }
  else {
    local_108 = local_1ec;
  }
  pbStack_20c = local_108;
  pbStack_210 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720e95;
  FUN_00574730();
  pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720e9e;
  FUN_004bc590();
  local_8 = 8;
  if ((local_f0 & 2) != 0) {
    local_f0 = local_f0 & 0xfffffffd;
    ~basic_string<>();
  }
  local_8 = 4;
  if ((local_f0 & 1) != 0) {
    local_f0 = local_f0 & 0xfffffffe;
    ~basic_string<>();
  }
  iVar3 = FUN_006b8f30();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_1ec,iVar3);
  local_130 = GetPolicy();
  local_8._0_1_ = 10;
  pbStack_20c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x720f49;
  local_124 = local_130;
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

