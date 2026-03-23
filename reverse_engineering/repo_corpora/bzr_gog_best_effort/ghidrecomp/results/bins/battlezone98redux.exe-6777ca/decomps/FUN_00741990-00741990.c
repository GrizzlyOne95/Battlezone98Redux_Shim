
undefined1 __thiscall FUN_00741990(int *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  code *pcVar5;
  undefined1 auStack_cc [160];
  undefined1 local_2c [16];
  undefined1 *local_1c;
  undefined1 local_15;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850dfb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = param_1;
  if ((*(char *)(param_2 + 0xb2) != '\0') &&
     (cVar1 = operator!=<>(param_2 + 0x98,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc),
     cVar1 != '\0')) {
    ExceptionList = local_10;
    return 0;
  }
  *(undefined1 *)(local_14 + 8) = 0;
  cVar1 = FUN_0056f780(local_14 + 10);
  if (cVar1 == '\0') {
    FID_conflict_operator_(param_3);
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xdc) {
      local_1c = (undefined1 *)0x0;
    }
    else {
      local_1c = auStack_cc;
    }
    pcVar5 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(local_1c,"CNetGameLobby::JoinLobby, requesting join to ",param_2 + 0x10);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar5);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
    FUN_007464e0(3);
    FUN_0073a740(param_2 + 0x10);
    (**(code **)(*local_14 + 0x7c))(local_2c,param_3);
    local_15 = 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    (**(code **)(*local_14 + 0x70))();
    FUN_007464e0(4);
    local_15 = 1;
  }
  ExceptionList = local_10;
  return local_15;
}

