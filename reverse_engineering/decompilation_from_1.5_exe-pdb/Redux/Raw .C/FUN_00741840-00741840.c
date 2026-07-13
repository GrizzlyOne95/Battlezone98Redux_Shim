
void FUN_00741840(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar5;
  code *pcVar6;
  code *pcVar7;
  code *pcVar8;
  undefined1 auStack_c8 [160];
  undefined1 local_28 [16];
  undefined1 *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b6b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DAT_008e8c7e = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xd8) {
    local_18 = (undefined1 *)0x0;
  }
  else {
    local_18 = auStack_c8;
  }
  pcVar8 = FUN_004bc8c0;
  uVar2 = FUN_00765a00(FUN_004bc8c0,uVar1);
  pcVar7 = FUN_006ab840;
  uVar3 = std::setw(CONCAT44(8,local_28));
  pcVar6 = FUN_00574a10;
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_18,"CNetGameLobby::JoinLobbyFromLaunchInvite, requesting join to ",
                        FUN_00574a10,uVar3,pcVar7,uVar2);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar6);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar4);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(pbVar4);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar8);
  pbVar5 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pbVar5);
  FUN_007464e0(3);
  uVar2 = FUN_00765a10();
  FID_conflict_operator_(uVar2);
  uVar2 = FUN_00765a00(local_14 + 0x29);
  (**(code **)(*local_14 + 0x7c))(uVar2);
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return;
}

