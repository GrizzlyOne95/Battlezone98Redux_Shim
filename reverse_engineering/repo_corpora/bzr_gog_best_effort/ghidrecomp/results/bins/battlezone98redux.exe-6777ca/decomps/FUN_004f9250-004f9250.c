
void __fastcall FUN_004f9250(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  MaterialManager *pMVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084a8f2;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = LensFlare::vftable;
  param_1[10] = LensFlare::vftable;
  param_1[0xb] = LensFlare::vftable;
  local_8 = 2;
  local_14 = uVar2;
  cVar1 = FUN_004c85a0(uVar2);
  if (cVar1 == '\0') {
    piVar3 = (int *)get();
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar3 + 0x58))();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
    local_8._0_1_ = 3;
    FUN_004c85d0();
    pMVar5 = Ogre::MaterialManager::getSingleton();
    (**(code **)(*(int *)pMVar5 + 0x38))(local_2c);
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
  }
  cVar1 = FUN_004c85a0(uVar2);
  if (cVar1 == '\0') {
    piVar3 = (int *)get();
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar3 + 0x58))();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_44,pbVar4);
    local_8._0_1_ = 4;
    FUN_004c85d0();
    pMVar5 = Ogre::MaterialManager::getSingleton();
    (**(code **)(*(int *)pMVar5 + 0x38))(local_44);
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
  }
  if (param_1[0x10] != 0) {
    FUN_004f9080(0);
  }
  if (param_1[0x11] != 0) {
    FUN_004f9080(0);
  }
  local_8._0_1_ = 1;
  FUN_004499a0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  Ogre::RenderQueueListener::~RenderQueueListener((RenderQueueListener *)(param_1 + 10));
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

