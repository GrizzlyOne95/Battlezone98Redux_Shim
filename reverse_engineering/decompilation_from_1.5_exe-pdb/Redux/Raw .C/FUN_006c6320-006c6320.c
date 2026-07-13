
void __fastcall FUN_006c6320(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined1 *puVar3;
  code *pcVar4;
  undefined4 uVar5;
  undefined1 auStack_168 [160];
  undefined1 local_c8 [8];
  undefined1 local_c0 [16];
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined1 *local_98;
  int local_94;
  undefined1 local_8d [25];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852341;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_94 = param_1;
  if (*(char *)(param_1 + 0xc34) == '\0') {
    *(undefined1 *)(param_1 + 0xc34) = 1;
    cVar1 = FUN_006ab7d0(local_14);
    if (cVar1 != '\0') {
      FUN_00574400(3,1);
      local_8 = 0;
      FUN_006cc0e0();
      local_8._0_1_ = 1;
      basic_string<>(&DAT_0087d178);
      local_8._0_1_ = 2;
      uVar2 = basic_string<>("DoEnterLounge");
      local_8._0_1_ = 3;
      local_ac = uVar2;
      local_a8 = uVar2;
      FUN_006cc100(local_2c);
      FUN_006dc070(uVar2);
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8d[0] = 1;
      basic_string<>("content");
      local_8._0_1_ = 4;
      puVar3 = local_8d;
      FUN_006cc100(local_44);
      FUN_006dc110(puVar3);
      local_8._0_1_ = 1;
      ~basic_string<>();
      if (&stack0x00000000 == (undefined1 *)0x178) {
        local_98 = (undefined1 *)0x0;
      }
      else {
        local_98 = auStack_168;
      }
      FUN_007d7970(local_98,local_c0,0,2);
      if (2 < DAT_008eda28) {
        local_a4 = GetPolicy(local_5c);
        local_8._0_1_ = 5;
        pcVar4 = FUN_004bc8c0;
        local_a0 = local_a4;
        FUN_0081e820("WebSocket Message Sent:\n",local_a4);
        uVar2 = FUN_0081e660();
        uVar2 = FUN_004bc590(uVar2);
        this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar2);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar4);
        local_8._0_1_ = 1;
        ~basic_string<>();
      }
      uVar2 = GetPolicy(local_74);
      local_8._0_1_ = 6;
      uVar5 = 1;
      puVar3 = local_c8;
      local_b0 = uVar2;
      local_9c = uVar2;
      FUN_00421ec0(puVar3,uVar2,1);
      FUN_006da6b0(puVar3,uVar2,uVar5);
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_006c3d30();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

