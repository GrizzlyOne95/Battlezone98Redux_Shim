
void FUN_0073b040(void)

{
  uint uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar3;
  code *pcVar4;
  undefined1 auStack_b8 [164];
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fcab;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0xc8) {
    local_14 = (undefined1 *)0x0;
  }
  else {
    local_14 = auStack_b8;
  }
  pcVar4 = FUN_004bc8c0;
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_14,"AuthListener::OnAuthLost : ",FUN_004bc8c0,uVar1);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar4);
  pbVar3 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar3);
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return;
}

