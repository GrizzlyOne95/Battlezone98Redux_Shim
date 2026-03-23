
undefined4 * FUN_0073d690(void)

{
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  code *pcVar4;
  undefined4 *puVar5;
  undefined1 auStack_b8 [160];
  undefined1 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085abfb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00508f90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *local_14 = CNetGameLobby::vftable;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  FUN_0073a6b0();
  FUN_0073a6b0();
  FUN_00428520();
  local_8._0_1_ = 3;
  basic_string<>();
  local_8._0_1_ = 4;
  basic_string<>();
  local_8._0_1_ = 5;
  basic_string<>();
  local_8._0_1_ = 6;
  *(undefined1 *)(local_14 + 0x30) = 1;
  FUN_00574400(3,1);
  local_8._0_1_ = 7;
  if (&stack0x00000000 == (undefined1 *)0xc8) {
    local_18 = (undefined1 *)0x0;
  }
  else {
    local_18 = auStack_b8;
  }
  pcVar4 = FUN_004bc8c0;
  pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_18,"CNetGameLobby::CNetGameLobby, matchmaking starting up");
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pcVar4);
  pbVar2 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pbVar2);
  *(undefined1 *)((int)local_14 + 0x21) = 0;
  local_14[0x14] = 0;
  local_14[0x15] = 0;
  FUN_0056f7e0();
  local_14[0xe] = 1;
  local_14[0x2f] = 0;
  *(undefined1 *)((int)local_14 + 0x62) = 0;
  *(undefined1 *)(local_14 + 0x28) = 0;
  *(undefined1 *)(local_14 + 8) = 0;
  uVar3 = 1;
  puVar5 = local_14;
  FUN_007659f0(1,local_14);
  FUN_00758af0(uVar3,puVar5);
  local_8 = CONCAT31(local_8._1_3_,6);
  FUN_00417f10();
  ExceptionList = local_10;
  return local_14;
}

