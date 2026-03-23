
void FUN_0050d4e0(void)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  MaterialManager *pMVar5;
  TextureManager *pTVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ac40;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  cVar1 = FUN_004c85a0(uVar2);
  if (cVar1 == '\0') {
    piVar3 = (int *)get();
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar3 + 0x58))();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
    local_8 = 0;
    FUN_004c85d0();
    pMVar5 = Ogre::MaterialManager::getSingleton();
    (**(code **)(*(int *)pMVar5 + 0x38))(local_2c);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  cVar1 = FUN_004c85a0(uVar2);
  if (cVar1 == '\0') {
    piVar3 = (int *)get();
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar3 + 0x58))();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_44,pbVar4);
    local_8 = 1;
    piVar3 = (int *)get();
    (**(code **)(*piVar3 + 0x4c))();
    FUN_004c85d0();
    pTVar6 = Ogre::TextureManager::getSingleton();
    (**(code **)(*(int *)pTVar6 + 0x38))(local_44);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

