
void __fastcall FUN_0077a7e0(Listener *param_1)

{
  uint uVar1;
  Root *this;
  RenderSystem *pRVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085e4f2;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = cRenderableTileClusterManager::vftable;
  local_8 = 5;
  this = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(this);
  (**(code **)(*(int *)pRVar2 + 0x1fc))(param_1,uVar1);
  FUN_0077bc30();
  FUN_0077aa20();
  if (*(int *)(param_1 + 0x70) != 0) {
    free(*(void **)(param_1 + 0x70));
  }
  if (*(int *)(param_1 + 0x80) != 0) {
    free(*(void **)(param_1 + 0x80));
  }
  Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::setNull
            ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)(param_1 + 4));
  Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::setNull
            ((SharedPtr<class_Ogre::HardwareIndexBuffer> *)(param_1 + 0xc));
  local_8._0_1_ = 4;
  FUN_006ca000();
  local_8._0_1_ = 3;
  FUN_004499a0();
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8._0_1_ = 1;
  Ogre::HardwareIndexBufferSharedPtr::~HardwareIndexBufferSharedPtr
            ((HardwareIndexBufferSharedPtr *)(param_1 + 0xc));
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr
            ((HardwareVertexBufferSharedPtr *)(param_1 + 4));
  local_8 = 0xffffffff;
  Ogre::RenderSystem::Listener::~Listener(param_1);
  ExceptionList = local_10;
  return;
}

