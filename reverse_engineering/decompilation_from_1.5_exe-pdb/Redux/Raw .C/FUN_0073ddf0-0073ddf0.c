
void FUN_0073ddf0(void)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_bc [160];
  undefined1 *local_1c;
  int *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850b3b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00747cf0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_00747fc0();
  *(undefined1 *)(local_14 + 8) = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xcc) {
    local_1c = (undefined1 *)0x0;
  }
  else {
    local_1c = auStack_bc;
  }
  pcVar5 = FUN_004bc8c0;
  uVar2 = FUN_004bc590(local_1c,"CNetGameLobby::ExitLounge called, leaving lobby ",local_14 + 10);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
  pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
  cVar1 = FUN_0073a900();
  if (cVar1 != '\0') {
    (**(code **)(*local_14 + 0x5c))();
  }
  FUN_007659f0();
  FUN_0073bb30();
  FUN_0056f7e0();
  local_18 = (int *)FUN_007647a0();
  if (local_18 != (int *)0x0) {
    (**(code **)(*local_18 + 4))(local_14 + 10);
  }
  *(undefined1 *)((int)local_14 + 0x21) = 1;
  local_14[0xe] = 1;
  FUN_00765c30();
  FUN_007464e0(0);
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return;
}

