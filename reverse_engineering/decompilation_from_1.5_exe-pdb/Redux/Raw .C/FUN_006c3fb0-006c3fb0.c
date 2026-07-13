
void FUN_006c3fb0(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined1 *puVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined1 auStack_1ec [176];
  undefined1 local_13c [8];
  undefined1 local_134 [16];
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
  undefined1 *local_f8;
  undefined4 local_f4;
  undefined1 local_ed;
  undefined1 local_ec [72];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851ee8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 != '\0') {
    FUN_00574400(3,1);
    local_8 = 0;
    FUN_006cc0e0();
    local_8._0_1_ = 1;
    basic_string<>(&DAT_0087d178);
    local_8._0_1_ = 2;
    uVar2 = basic_string<>("CreateLobby");
    local_8._0_1_ = 3;
    local_110 = uVar2;
    local_10c = uVar2;
    FUN_006cc100(local_44);
    FUN_006dc070(uVar2);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("content");
    local_8._0_1_ = 4;
    uVar2 = FUN_006cc0e0();
    local_8._0_1_ = 5;
    local_120 = uVar2;
    local_108 = uVar2;
    FUN_006cc100(local_2c);
    uVar2 = FUN_006dc0c0(uVar2);
    local_f4 = FUN_006db8f0(uVar2);
    local_8._0_1_ = 4;
    FUN_006c3d30();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("memberLimit");
    local_8._0_1_ = 6;
    puVar3 = &stack0x00000004;
    FUN_006cc100(local_5c);
    FUN_006dc0f0(puVar3);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_ed = 0;
    basic_string<>("isPrivate");
    local_8._0_1_ = 7;
    puVar3 = &local_ed;
    FUN_006cc100(local_8c);
    FUN_006dc110(puVar3);
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("password");
    local_8._0_1_ = 8;
    uVar2 = basic_string<>(&DAT_008a1ad8);
    local_8._0_1_ = 9;
    local_114 = uVar2;
    local_104 = uVar2;
    FUN_006cc100(local_74);
    FUN_006dc070(uVar2);
    local_8._0_1_ = 8;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    if (&stack0x00000000 == (undefined1 *)0x1fc) {
      local_f8 = (undefined1 *)0x0;
    }
    else {
      local_f8 = auStack_1ec;
    }
    FUN_007d7970(local_f8,local_134,0,2);
    if (2 < DAT_008eda28) {
      local_124 = GetPolicy(local_ec);
      local_8._0_1_ = 10;
      pcVar4 = FUN_004bc8c0;
      local_11c = local_124;
      FUN_0081e820("WebSocket Message Sent:\n",local_124);
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar4);
      local_8._0_1_ = 1;
      ~basic_string<>();
    }
    uVar2 = GetPolicy(local_a4);
    local_8._0_1_ = 0xb;
    uVar5 = 1;
    puVar3 = local_13c;
    local_118 = uVar2;
    local_100 = uVar2;
    FUN_00421ec0(puVar3,uVar2,1);
    FUN_006da6b0(puVar3,uVar2,uVar5);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c3d30();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

