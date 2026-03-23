
void __thiscall FUN_006aabf0(int param_1,int *param_2)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  int iVar4;
  code *pcVar5;
  undefined1 auStack_c0 [160];
  int local_20;
  int *local_1c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe9b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1c = param_2;
  if (((*(int *)(param_1 + 0x10) == *param_2) && (*(int *)(param_1 + 0x14) == param_2[1])) &&
     (param_2[2] != 1)) {
    local_20 = param_1;
    local_18 = param_1;
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0xd0) {
      local_14 = (undefined1 *)0x0;
    }
    else {
      local_14 = auStack_c0;
    }
    pcVar5 = FUN_004bc8c0;
    iVar4 = param_2[2];
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_14,"StatsStored - failed : ",iVar4,FUN_004bc8c0,uVar1);
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,iVar4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar5);
    pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  return;
}

