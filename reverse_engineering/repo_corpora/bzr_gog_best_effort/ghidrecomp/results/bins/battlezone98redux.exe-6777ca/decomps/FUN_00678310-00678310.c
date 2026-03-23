
void FUN_00678310(void)

{
  undefined4 uVar1;
  HardwareIndexBufferSharedPtr local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  HardwareBufferManager *local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f309;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_0067ac40(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  (**(code **)(*local_14 + 0x48))(uVar1);
  uVar1 = FUN_0041f870();
  FUN_007d6a70("%s: add index buffer [%d]\n",uVar1);
  local_18 = Ogre::HardwareBufferManager::getSingleton();
  local_20 = (**(code **)(*(int *)local_18 + 0x24))(local_28,0,0x18000,0xe,0);
  local_8 = 0;
  local_1c = local_20;
  FUN_0067acf0(local_20);
  local_8 = 0xffffffff;
  Ogre::HardwareIndexBufferSharedPtr::~HardwareIndexBufferSharedPtr(local_28);
  ExceptionList = local_10;
  return;
}

