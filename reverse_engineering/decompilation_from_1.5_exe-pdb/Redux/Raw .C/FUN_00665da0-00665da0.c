
void FUN_00665da0(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  LogManager *this;
  LogMessageLevel LVar4;
  bool bVar5;
  undefined1 auStack_e8 [164];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_44;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_40;
  undefined1 local_3c [8];
  int *local_34;
  undefined1 *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e14b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  (**(code **)(*param_1 + 0x48))(local_3c,param_2,AUTODETECT_RESOURCE_GROUP_NAME_exref,local_14);
  local_8 = 0;
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    local_34 = (int *)get();
    (**(code **)(*local_34 + 0x4c))();
    (**(code **)(*param_1 + 0x38))(param_2);
    cVar1 = (**(code **)(*param_1 + 0x54))(param_2);
    if (cVar1 != '\0') {
      FUN_00574400(3,1);
      local_8._0_1_ = 1;
      if (&stack0x00000000 == (undefined1 *)0xf8) {
        local_30 = (undefined1 *)0x0;
      }
      else {
        local_30 = auStack_e8;
      }
      uVar2 = FUN_004bc590(local_30,"Resource still exists (unload failed): ",param_2);
      FUN_00574730(uVar2);
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               GetPolicy(local_2c);
      local_8._0_1_ = 2;
      bVar5 = false;
      LVar4 = 2;
      local_44 = pbVar3;
      local_40 = pbVar3;
      this = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(this,pbVar3,LVar4,bVar5);
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
    }
    local_8 = 0xffffffff;
    FUN_004499a0();
  }
  else {
    local_8 = 0xffffffff;
    FUN_004499a0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

