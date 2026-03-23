
void FUN_006c4350(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined1 *puVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined1 auStack_1c8 [176];
  undefined1 local_118 [8];
  undefined1 local_110 [16];
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined1 *local_dc;
  undefined4 local_d8;
  undefined1 local_d4 [48];
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
  puStack_c = &LAB_00851f7d;
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
    uVar2 = basic_string<>("CreateGame");
    local_8._0_1_ = 3;
    local_fc = uVar2;
    local_f4 = uVar2;
    FUN_006cc100(local_2c);
    FUN_006dc070(uVar2);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("content");
    local_8._0_1_ = 4;
    uVar2 = FUN_006cc0e0();
    local_8._0_1_ = 5;
    local_f8 = uVar2;
    local_f0 = uVar2;
    FUN_006cc100(local_44);
    uVar2 = FUN_006dc0c0(uVar2);
    local_d8 = FUN_006db8f0(uVar2);
    local_8._0_1_ = 4;
    FUN_006c3d30();
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("memberLimit");
    local_8._0_1_ = 6;
    puVar3 = (undefined1 *)&param_1;
    FUN_006cc100(local_5c);
    FUN_006dc0f0(puVar3);
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("isPrivate");
    local_8._0_1_ = 7;
    puVar3 = (undefined1 *)&param_2;
    FUN_006cc100(local_8c);
    FUN_006dc140(puVar3);
    local_8._0_1_ = 1;
    ~basic_string<>();
    basic_string<>("password");
    local_8._0_1_ = 8;
    uVar2 = param_3;
    FUN_006cc100(local_74);
    FUN_006dc0a0(uVar2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    if (&stack0x00000000 == (undefined1 *)0x1d8) {
      local_dc = (undefined1 *)0x0;
    }
    else {
      local_dc = auStack_1c8;
    }
    FUN_007d7970(local_dc,local_110,0,2);
    if (2 < DAT_008eda28) {
      local_ec = GetPolicy(local_a4);
      local_8._0_1_ = 9;
      pcVar4 = FUN_004bc8c0;
      local_e8 = local_ec;
      FUN_0081e820("WebSocket Message Sent:\n",local_ec);
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar4);
      local_8._0_1_ = 1;
      ~basic_string<>();
    }
    uVar2 = GetPolicy(local_d4);
    local_8._0_1_ = 10;
    uVar5 = 1;
    puVar3 = local_118;
    local_100 = uVar2;
    local_e4 = uVar2;
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

