
void __fastcall FUN_0073d510(undefined4 *param_1)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  undefined4 uVar4;
  code *pcVar5;
  undefined4 *puVar6;
  undefined1 auStack_b8 [160];
  undefined1 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085abfb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = CNetGameLobby::vftable;
  local_8 = 6;
  local_14 = param_1;
  FUN_00574400(3,1);
  local_8._0_1_ = 7;
  if (&stack0x00000000 == (undefined1 *)0xc8) {
    local_18 = (undefined1 *)0x0;
  }
  else {
    local_18 = auStack_b8;
  }
  pcVar5 = FUN_004bc8c0;
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_18,"CNetGameLobby::~CNetGameLobby, matchmaking shutting down",
                        FUN_004bc8c0,uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
  pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
  uVar4 = 1;
  puVar6 = local_14;
  FUN_007659f0(1,local_14);
  FUN_00758b20(uVar4,puVar6);
  local_8._0_1_ = 6;
  FUN_00417f10();
  local_8._0_1_ = 5;
  ~basic_string<>();
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8._0_1_ = 3;
  ~basic_string<>();
  local_8._0_1_ = 2;
  FUN_0045c7d0();
  local_8._0_1_ = 1;
  ~vector<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00747c50();
  local_8 = 0xffffffff;
  FUN_00758a10();
  ExceptionList = local_10;
  return;
}

