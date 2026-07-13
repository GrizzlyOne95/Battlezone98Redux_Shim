
void FUN_0067a4d0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  undefined4 uVar1;
  uint uStack_44;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_34 [12];
  undefined4 local_28;
  undefined4 local_24;
  MaterialManager *local_20;
  int local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084f468;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_44;
  ExceptionList = &local_10;
  local_8 = 0;
  local_20 = Ogre::MaterialManager::getSingleton();
  local_28 = Ogre::MaterialManager::getByName(local_20,local_34,param_1);
  local_8._0_1_ = 1;
  local_24 = local_28;
  FUN_00449910(local_28);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_15 = FUN_004c85a0();
  if (local_15 != '\0') {
    uVar1 = FUN_0041f870();
    uVar1 = FUN_0041f870(uVar1);
    FUN_007d6a70("DynamicGeometry: material \"%s\" in group \"%s\" not found\n",uVar1);
    FUN_00449910(*(int *)(local_1c + 0x38) + 0x140);
  }
  FUN_0067a5ed();
  return;
}

