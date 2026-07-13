
void FUN_00740a90(undefined1 param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_b8 [160];
  undefined1 *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fcab;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar1 = FUN_0073a900(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 != '\0') {
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xc8) {
      local_18 = (undefined1 *)0x0;
    }
    else {
      local_18 = auStack_b8;
    }
    pcVar5 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(local_18,"CNetGameLobby::ExitLobby called, leaving lobby ",local_14 + 10);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
    (**(code **)(*local_14 + 0x5c))();
    FUN_007659f0();
    FUN_0073bb30();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  FUN_00747fc0();
  FUN_0056f7e0();
  *(undefined1 *)((int)local_14 + 0x21) = 1;
  local_14[0xe] = 1;
  FUN_007464e0(2);
  (**(code **)(*local_14 + 0x70))();
  *(undefined1 *)(local_14 + 8) = param_1;
  ExceptionList = local_10;
  return;
}

