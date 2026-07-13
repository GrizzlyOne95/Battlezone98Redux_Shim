
void __fastcall FUN_0074c190(int param_1)

{
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar2;
  code *pcVar3;
  undefined1 auStack_c0 [160];
  undefined8 local_20;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe9b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x54) == 0) {
    local_14 = param_1;
    local_20 = FUN_00822ea0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    *(undefined8 *)(local_14 + 0x80) = local_20;
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xd0) {
      local_18 = (undefined1 *)0x0;
    }
    else {
      local_18 = auStack_c0;
    }
    pcVar3 = FUN_004bc8c0;
    pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_18,"BZRNetLobby::GetLobbyList called, requesting lobbies");
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pcVar3);
    pbVar2 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar1 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,pbVar2);
    *(undefined4 *)(local_14 + 0x54) = 1;
    DAT_00945460 = 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return;
}

