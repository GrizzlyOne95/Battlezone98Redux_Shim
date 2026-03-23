
void FUN_00740be0(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_f0 [160];
  uint local_50;
  int local_4c;
  uint local_48;
  int local_44;
  undefined1 *local_40;
  undefined8 local_3c;
  int local_34;
  int *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085afd3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = FUN_00822ea0(local_14);
  local_34 = FUN_006cc050();
  if ((char)local_30[0x28] == '\x01') {
    FUN_0079d710();
    FUN_00795cf0();
    FUN_0078a640();
    uVar2 = FUN_0081cb40("multi_message","kick_room");
    basic_string<>(uVar2);
    local_8 = 0;
    FUN_00745770(local_2c);
    local_8 = 0xffffffff;
    ~basic_string<>();
    *(undefined1 *)(local_30 + 0x28) = 0;
  }
  else {
    cVar1 = FUN_0073a900();
    if (cVar1 == '\0') {
      local_50 = (uint)local_3c - local_30[0x20];
      local_4c = (local_3c._4_4_ - local_30[0x21]) - (uint)((uint)local_3c < (uint)local_30[0x20]);
      if (((local_4c != 0) || (30000 < local_50)) && (local_30[0x15] != 0)) {
        local_30[0x15] = 0;
      }
      local_48 = (uint)local_3c - local_30[0x20];
      local_44 = (local_3c._4_4_ - local_30[0x21]) - (uint)((uint)local_3c < (uint)local_30[0x20]);
      if ((((local_44 != 0) || (15000 < local_48)) && (*(char *)((int)local_30 + 0x21) != '\0')) &&
         ((((local_34 == 2 || (local_34 == 3)) || (local_34 == 4)) && (local_30[0x15] == 0)))) {
        (**(code **)(*local_30 + 0x70))();
      }
    }
    else {
      FUN_00574400(3,1);
      local_8 = 1;
      if (&stack0x00000000 == (undefined1 *)0x100) {
        local_40 = (undefined1 *)0x0;
      }
      else {
        local_40 = auStack_f0;
      }
      pcVar5 = FUN_004bc8c0;
      uVar2 = FUN_004bc590(local_40,"CNetGameLobby::RunCallbacks, requesting to join lobby ",
                           local_30 + 0x10);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
      pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
      FUN_007464e0(3);
      *(undefined1 *)(local_30 + 8) = 0;
      (**(code **)(*local_30 + 0x7c))(local_30 + 0x10,local_30 + 0x29);
      FUN_0056f7e0();
      FUN_005d5300();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

