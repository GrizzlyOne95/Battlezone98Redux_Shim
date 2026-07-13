
void FUN_0073df60(char param_1,int *param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_224 [176];
  undefined1 auStack_174 [176];
  undefined1 auStack_c4 [160];
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085aca1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_1 == '\0') {
    FUN_00574400(3,1);
    local_8 = 2;
    if (&stack0x00000000 == (undefined1 *)0x234) {
      local_24 = (undefined1 *)0x0;
    }
    else {
      local_24 = auStack_224;
    }
    pcVar5 = FUN_004bc8c0;
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_24,
                          "Failed to create lobby (lost connection to Steam back-end servers).  Steam Error: "
                         );
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
    *(undefined1 *)((int)local_14 + 0x62) = 0;
    *(undefined1 *)((int)local_14 + 0x21) = 1;
    FUN_007464e0(2);
    *(undefined1 *)((int)local_14 + 0x20) = 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    cVar1 = FUN_0073a900(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    if (cVar1 == '\0') {
      FUN_00574400(3,1);
      local_8 = 1;
      if (&stack0x00000000 == (undefined1 *)0x184) {
        local_1c = (undefined1 *)0x0;
      }
      else {
        local_1c = auStack_174;
      }
      pcVar5 = FUN_004bc8c0;
      uVar2 = FUN_004bc590(local_1c,"CNetGameLobby::OnLobbyCreated, joined ",param_2);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
      pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    else {
      FUN_00574400(3,1);
      local_8 = 0;
      if (&stack0x00000000 == (undefined1 *)0xd4) {
        local_20 = (undefined1 *)0x0;
      }
      else {
        local_20 = auStack_c4;
      }
      pcVar5 = FUN_004bc8c0;
      uVar2 = FUN_004bc590(local_20,"CNetGameLobby::OnLobbyCreated, leaving prior lobby ",
                           local_14 + 10,", joined ",param_2);
      uVar2 = FUN_0073ba70(uVar2);
      uVar2 = FUN_004bc590(uVar2);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
      pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
      (**(code **)(*local_14 + 0x5c))();
      FUN_007659f0();
      FUN_0073bb30();
      FUN_0056f7e0();
      FUN_00747fc0();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
    local_14[10] = *param_2;
    local_14[0xb] = param_2[1];
    local_14[0xc] = param_2[2];
    local_14[0xd] = param_2[3];
    local_18 = (int *)FUN_007647a0();
    if (local_18 != (int *)0x0) {
      (**(code **)(*local_18 + 4))(local_14 + 10);
    }
    FUN_007436c0(local_14 + 10);
  }
  ExceptionList = local_10;
  return;
}

