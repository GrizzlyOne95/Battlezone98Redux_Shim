
void __thiscall FUN_0073e240(int *param_1,char param_2,int *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  code *pcVar6;
  undefined1 auStack_230 [176];
  undefined1 auStack_180 [160];
  undefined4 local_e0;
  undefined4 local_dc;
  int local_d8;
  undefined1 *local_d4;
  undefined1 *local_d0;
  int local_cc;
  int *local_c8;
  int local_c4;
  int *local_c0;
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ad17;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_c0 = param_1;
  if (param_2 == '\0') {
    local_cc = param_4;
    if (param_4 == 0) {
      uVar2 = FUN_0081cb40("multi_error","kick_room");
      basic_string<>(uVar2);
      local_8 = 1;
      FUN_00745770(local_5c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else if (param_4 == 1) {
      uVar2 = FUN_0081cb40("multi_error","game_full");
      basic_string<>(uVar2);
      local_8 = 0;
      FUN_00745770(local_2c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else if (param_4 == 2) {
      uVar2 = FUN_0081cb40("multi_error","game_not_avail");
      basic_string<>(uVar2);
      local_8 = 2;
      FUN_00745770(local_8c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    pcVar6 = FUN_004bc8c0;
    pcVar5 = FUN_0056f740;
    FUN_0081e820("Failed to enter requested lobby:",param_3," Reason: ");
    uVar2 = FUN_0081e660();
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_0073ba70(uVar2);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,param_4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar6);
    *(undefined1 *)((int)local_c0 + 0x21) = 1;
    FUN_007464e0(2);
    *(undefined1 *)(local_c0 + 8) = 1;
    (**(code **)(*local_c0 + 0x70))();
  }
  else if (*(char *)((int)param_1 + 0x62) == '\0') {
    pcVar5 = FUN_004bc8c0;
    FUN_0081e820("Entered room: ",param_3,FUN_004bc8c0,local_14);
    uVar2 = FUN_0081e660();
    uVar2 = FUN_004bc590(uVar2);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    cVar1 = FUN_0073ba10(param_3);
    if (cVar1 != '\0') {
      cVar1 = FUN_0073a900();
      if (cVar1 != '\0') {
        FUN_00574400(3,1);
        local_8 = 3;
        if (&stack0x00000000 == (undefined1 *)0x190) {
          local_d4 = (undefined1 *)0x0;
        }
        else {
          local_d4 = auStack_180;
        }
        pcVar5 = FUN_004bc8c0;
        uVar2 = FUN_004bc590(local_d4,"CNetGameLobby::OnLobbyEntered, leaving prior lobby ",
                             local_c0 + 10);
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
        pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
        FUN_0081e820();
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
        (**(code **)(*local_c0 + 0x5c))();
        FUN_007659f0();
        FUN_0073bb30();
        FUN_00747fc0();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      local_c0[10] = *param_3;
      local_c0[0xb] = param_3[1];
      local_c0[0xc] = param_3[2];
      local_c0[0xd] = param_3[3];
      local_d8 = FUN_007659f0();
      if (local_d8 != 0) {
        FUN_0073bb30();
      }
      local_c8 = (int *)FUN_007647a0();
      if (local_c8 != (int *)0x0) {
        (**(code **)(*local_c8 + 4))(local_c0 + 10);
      }
      local_c0[0xe] = 1;
      local_c4 = FUN_007470b0(local_c0 + 10,1);
      *(undefined1 *)((int)local_c0 + 0x21) = *(undefined1 *)(local_c4 + 0xb0);
      FUN_0041f830();
      FUN_00743f40(local_c4,0);
      FUN_00742900(local_c4);
      FUN_00574400(3,1);
      local_8 = 4;
      if (&stack0x00000000 == (undefined1 *)0x240) {
        local_d0 = (undefined1 *)0x0;
      }
      else {
        local_d0 = auStack_230;
      }
      FUN_007647a0();
      uVar2 = FUN_00583e30();
      FUN_0073ba70(local_d0,uVar2);
      local_e0 = GetPolicy(local_bc);
      local_8._0_1_ = 5;
      local_dc = local_e0;
      uVar2 = FUN_0041f870();
      basic_string<>(uVar2);
      local_8._0_1_ = 6;
      basic_string<>("friendID");
      local_8._0_1_ = 7;
      (**(code **)(*local_c0 + 0x1c))(local_c0 + 10,local_a4,local_44);
      local_8._0_1_ = 6;
      ~basic_string<>();
      local_8._0_1_ = 5;
      ~basic_string<>();
      local_8._0_1_ = 4;
      ~basic_string<>();
      FUN_007464e0(4);
      basic_string<>("fully entered lobby");
      local_8._0_1_ = 8;
      FUN_007472d0(local_74);
      local_8 = CONCAT31(local_8._1_3_,4);
      ~basic_string<>();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  else {
    pcVar5 = FUN_004bc8c0;
    FUN_0081e820("Entered room on create: ",param_3,FUN_004bc8c0,local_14);
    uVar2 = FUN_0081e660();
    uVar2 = FUN_004bc590(uVar2);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

