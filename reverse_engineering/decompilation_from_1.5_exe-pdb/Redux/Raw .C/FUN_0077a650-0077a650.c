
Listener * __fastcall FUN_0077a650(Listener *param_1)

{
  uint uVar1;
  void *pvVar2;
  Root *this;
  RenderSystem *pRVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e4f2;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  Ogre::RenderSystem::Listener::Listener(param_1);
  local_8 = 0;
  *(undefined ***)param_1 = cRenderableTileClusterManager::vftable;
  Ogre::HardwareVertexBufferSharedPtr::HardwareVertexBufferSharedPtr
            ((HardwareVertexBufferSharedPtr *)(param_1 + 4));
  local_8._0_1_ = 1;
  Ogre::HardwareIndexBufferSharedPtr::HardwareIndexBufferSharedPtr
            ((HardwareIndexBufferSharedPtr *)(param_1 + 0xc));
  local_8._0_1_ = 2;
  param_1[0x14] = (Listener)0x1;
  basic_string<>(uVar1);
  local_8._0_1_ = 3;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x30));
  local_8._0_1_ = 4;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,5);
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0x9600;
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x74) << 1;
  param_1[0x7c] = (Listener)0x1;
  *(undefined4 *)(param_1 + 0x80) = 0;
  param_1[0x84] = (Listener)0x1;
  param_1[0x85] = (Listener)0x0;
  pvVar2 = malloc(*(size_t *)(param_1 + 0x78));
  *(void **)(param_1 + 0x70) = pvVar2;
  this = Ogre::Root::getSingleton();
  pRVar3 = Ogre::Root::getRenderSystem(this);
  (**(code **)(*(int *)pRVar3 + 0x1f8))(param_1);
  pvVar2 = calloc(0x24c1,0x10);
  *(void **)(param_1 + 0x80) = pvVar2;
  FUN_0077c230();
  ExceptionList = local_10;
  return param_1;
}

