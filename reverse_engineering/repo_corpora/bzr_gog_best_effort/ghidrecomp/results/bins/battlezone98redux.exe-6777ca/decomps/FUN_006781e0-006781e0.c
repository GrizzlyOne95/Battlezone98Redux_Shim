
void FUN_006781e0(void)

{
  undefined4 uVar1;
  wchar_t *pwVar2;
  HardwareVertexBufferSharedPtr local_34 [8];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int *local_20;
  HardwareBufferManager *local_1c;
  HardwareBufferManager *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f2d9;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_0067ac40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  (**(code **)(*local_14 + 0x48))(uVar1);
  uVar1 = FUN_0041f870();
  FUN_007d6a70("%s: add vertex buffer [%d]\n",uVar1);
  local_18 = Ogre::HardwareBufferManager::getSingleton();
  local_28 = (**(code **)(*(int *)local_18 + 0x20))(local_34,local_14[0x53],0x10000,0xe,0);
  local_8 = 0;
  local_24 = local_28;
  FUN_0067ab00(local_28);
  local_8 = 0xffffffff;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr(local_34);
  local_1c = Ogre::HardwareBufferManager::getSingletonPtr();
  local_2c = (**(code **)(*(int *)local_1c + 0x3c))();
  FUN_0041ff90(&local_2c);
  pwVar2 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)(local_14 + 0x5b));
  local_20 = *(int **)pwVar2;
  pwVar2 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)(local_14 + 0x55));
  (**(code **)(*local_20 + 4))(0,pwVar2);
  ExceptionList = local_10;
  return;
}

