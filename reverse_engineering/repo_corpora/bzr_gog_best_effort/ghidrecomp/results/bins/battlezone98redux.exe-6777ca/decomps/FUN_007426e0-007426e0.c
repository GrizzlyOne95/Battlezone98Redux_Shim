
void __thiscall FUN_007426e0(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  undefined1 auStack_b8 [160];
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fcab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined1 *)(param_1 + 0x20) = 0;
  local_14 = param_1;
  FID_conflict_operator_(param_4);
  *(undefined1 *)(local_14 + 0x60) = param_2;
  FID_conflict_operator_(param_3);
  *(undefined1 *)(local_14 + 0x61) = 0;
  *(undefined1 *)(local_14 + 0x62) = 1;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xc8) {
    local_18 = (undefined1 *)0x0;
  }
  else {
    local_18 = auStack_b8;
  }
  pcVar4 = FUN_004bc8c0;
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_18,"CNetGameLobby::CreateLobby called, creating game",FUN_004bc8c0,
                        uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar4);
  pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
  FUN_007464e0(3);
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return;
}

