
void __fastcall FUN_00677fd0(MovableObject *param_1)

{
  uint uVar1;
  Root *this;
  RenderSystem *pRVar2;
  HardwareBufferManager *pHVar3;
  MovableObject *local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084f2ae;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = DynamicGeometry::vftable;
  *(undefined ***)(param_1 + 4) = DynamicGeometry::vftable;
  *(undefined ***)(param_1 + 0xd0) = DynamicGeometry::vftable;
  *(undefined ***)(param_1 + 0xd4) = DynamicGeometry::vftable;
  local_8 = 0xc;
  if (param_1 == (MovableObject *)0x0) {
    local_18 = (MovableObject *)0x0;
  }
  else {
    local_18 = param_1 + 0xd0;
  }
  this = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(this);
  (**(code **)(*(int *)pRVar2 + 0x1fc))(local_18,uVar1);
  pHVar3 = Ogre::HardwareBufferManager::getSingletonPtr();
  (**(code **)(*(int *)pHVar3 + 0x38))(*(undefined4 *)(param_1 + 0x148));
  FUN_00678450();
  local_8._0_1_ = 0xb;
  _eh_vector_destructor_iterator_(param_1 + 0x1b0,0xc,2,FUN_0041fe20);
  local_8._0_1_ = 10;
  FUN_0041fe20();
  local_8._0_1_ = 9;
  FUN_0041fe20();
  local_8._0_1_ = 8;
  FUN_0041fe20();
  local_8._0_1_ = 7;
  FUN_0067ae10();
  local_8._0_1_ = 6;
  FUN_0041fe20();
  local_8._0_1_ = 5;
  FUN_0041fe20();
  local_8._0_1_ = 4;
  FUN_0067ac20();
  local_8._0_1_ = 3;
  FUN_004499a0();
  local_8._0_1_ = 2;
  Ogre::AxisAlignedBox::~AxisAlignedBox((AxisAlignedBox *)(param_1 + 0xdc));
  local_8._0_1_ = 1;
  Ogre::Camera::Listener::~Listener((Listener *)(param_1 + 0xd4));
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::RenderSystem::Listener::~Listener((Listener *)(param_1 + 0xd0));
  local_8 = 0xffffffff;
  Ogre::MovableObject::~MovableObject(param_1);
  ExceptionList = local_10;
  return;
}

