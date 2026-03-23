
void __thiscall FUN_007408c0(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar5;
  code *pcVar6;
  undefined1 auStack_bc [160];
  undefined1 *local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b3b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  cVar1 = FUN_0056f780(param_1 + 0x28);
  if (cVar1 == '\0') {
    if (DAT_00918324 == 0) {
      FUN_0081e0c0("CNetGameLobby::OnGameLobbyJoinRequested, Exiting game because of steam invite acceptance\n"
                   ,uVar2);
      FUN_00765bb0(param_2,param_3);
      DAT_009183ec = 1;
      DAT_009455de = 1;
      DAT_00917f4d = 1;
      FUN_00434170(2);
      DAT_00918328 = 0;
    }
    else {
      FUN_00574400(3,1);
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0xcc) {
        local_18 = (undefined1 *)0x0;
      }
      else {
        local_18 = auStack_bc;
      }
      uVar3 = FUN_004bc590(local_18,
                           "CNetGameLobby::OnGameLobbyJoinRequested, pending request to join lobby "
                           ,param_2);
      FUN_0073ba70(uVar3);
      if (&stack0x00000000 == (undefined1 *)0xcc) {
        local_1c = (undefined1 *)0x0;
      }
      else {
        local_1c = auStack_bc;
      }
      pcVar6 = FUN_004bc8c0;
      uVar3 = FUN_004bc590(local_1c," with friend ",param_4);
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
      pbVar5 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pbVar5);
      FUN_007464e0(3);
      FID_conflict_operator_(param_3);
      *(undefined4 *)(local_14 + 0x40) = *param_2;
      *(undefined4 *)(local_14 + 0x44) = param_2[1];
      *(undefined4 *)(local_14 + 0x48) = param_2[2];
      *(undefined4 *)(local_14 + 0x4c) = param_2[3];
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  else {
    FUN_007d6a70(
                "CNetGameLobby::DoOnGameLobbyJoinRequested but lobbyId == this->m_activeLobby to aborting execution"
                );
  }
  ExceptionList = local_10;
  return;
}

