
void __fastcall FUN_007a4070(int param_1)

{
  bool bVar1;
  int iVar2;
  ResourceGroupManager *this;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x38) == -1) {
    (**(code **)(**(int **)(param_1 + 0x1c) + 0x24))(0);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x1c) + 0x24))(1,local_14);
    iVar2 = FUN_00752d30(*(undefined4 *)(param_1 + 0x38));
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(iVar2 + 0x54));
    local_8 = 0;
    pbVar4 = local_2c;
    this = Ogre::ResourceGroupManager::getSingleton();
    bVar1 = Ogre::ResourceGroupManager::resourceExistsInAnyGroup(this,pbVar4);
    if (bVar1) {
      uVar3 = FUN_0041f870();
      FUN_007d2870(uVar3);
      (**(code **)(**(int **)(param_1 + 0x1c) + 0x24))(1);
    }
    else {
      (**(code **)(**(int **)(param_1 + 0x1c) + 0x24))(0);
    }
    FUN_00752d30(*(undefined4 *)(param_1 + 0x38));
    uVar3 = FUN_0041f870();
    (**(code **)(**(int **)(param_1 + 0x40) + 0x3c))(uVar3);
    uVar3 = FUN_007ccaf0();
    FUN_007cca20(uVar3);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

