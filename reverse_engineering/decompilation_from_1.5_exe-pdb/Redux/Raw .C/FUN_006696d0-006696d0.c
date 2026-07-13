
void __thiscall FUN_006696d0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_74 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e760;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  iVar3 = FUN_00669800(param_2);
  if (iVar3 == 0) {
    FUN_006678e0(local_44,param_1 + 4,param_2,uVar2);
    local_8 = 0;
    uVar4 = FUN_0041f870(local_74);
    iVar3 = FUN_00666ce0(uVar4);
    if (iVar3 == 0) {
      uVar4 = FUN_0041f870();
      cVar1 = FUN_00667860(uVar4);
      if (cVar1 != '\0') {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)(param_1 + 4));
        local_8._0_1_ = 1;
        Ogre::StringUtil::toLowerCase(local_2c);
        Ogre::StringUtil::startsWith(local_44,local_2c,true);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
      }
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

