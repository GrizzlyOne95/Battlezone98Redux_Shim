
void FUN_00751560(void)

{
  uint uVar1;
  int iVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_d4 [160];
  undefined8 local_34;
  undefined8 local_2c;
  int *local_24;
  int *local_20;
  int *local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe6b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = FUN_007508c0(uVar1);
  if ((iVar2 != 0) && (*(int *)(local_14 + 0x54) == 0)) {
    local_2c = FUN_00822ea0();
    *(undefined8 *)(local_14 + 0x80) = local_2c;
    local_20 = (int *)FUN_007508c0(uVar1);
    (**(code **)(*local_20 + 0x28))(32000);
    local_24 = (int *)FUN_007508c0();
    (**(code **)(*local_24 + 0x14))("GameVersion",PTR_s_2_2_301_008eda3c,0);
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xe4) {
      local_18 = (undefined1 *)0x0;
    }
    else {
      local_18 = auStack_d4;
    }
    pcVar5 = FUN_004bc8c0;
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_18,"CNetGameLobby::GetLobbyList called, requesting lobbies");
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
    local_1c = (int *)FUN_007508c0();
    local_34 = (**(code **)(*local_1c + 0x10))();
    FUN_00752250(local_34,local_14,FUN_00751880);
    *(undefined4 *)(local_14 + 0x54) = 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return;
}

