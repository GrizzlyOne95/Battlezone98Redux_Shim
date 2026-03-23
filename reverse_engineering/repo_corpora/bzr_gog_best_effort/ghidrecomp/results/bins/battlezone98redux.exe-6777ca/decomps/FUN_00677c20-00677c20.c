
void __thiscall
FUN_00677c20(MovableObject *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  undefined4 uVar1;
  MaterialManager *this;
  Root *this_00;
  int iVar2;
  code *pcVar3;
  MovableObject *pMVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_4c [8];
  undefined4 local_44;
  undefined4 local_40;
  HardwareBufferManager *local_3c;
  MovableObject *local_38;
  RenderSystem *local_34;
  MovableObject *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f1be;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  Ogre::MovableObject::MovableObject(param_1,param_2);
  local_8 = 0;
  Ogre::RenderSystem::Listener::Listener((Listener *)(local_30 + 0xd0));
  local_8._0_1_ = 1;
  Ogre::Camera::Listener::Listener((Listener *)(local_30 + 0xd4));
  local_8._0_1_ = 2;
  *(undefined ***)local_30 = DynamicGeometry::vftable;
  *(undefined ***)(local_30 + 4) = DynamicGeometry::vftable;
  *(undefined ***)(local_30 + 0xd0) = DynamicGeometry::vftable;
  *(undefined ***)(local_30 + 0xd4) = DynamicGeometry::vftable;
  local_30[0xd8] = (MovableObject)0x1;
  Ogre::AxisAlignedBox::AxisAlignedBox
            ((AxisAlignedBox *)(local_30 + 0xdc),(AxisAlignedBox *)BOX_NULL_exref);
  local_8._0_1_ = 3;
  *(undefined4 *)(local_30 + 0xfc) = 0;
  pcVar3 = IDENTITY_exref;
  pMVar4 = local_30 + 0x100;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pMVar4 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    pMVar4 = pMVar4 + 4;
  }
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(local_30 + 0x140));
  local_8._0_1_ = 4;
  *(undefined4 *)(local_30 + 0x148) = 0;
  *(undefined4 *)(local_30 + 0x14c) = 0;
  local_30[0x150] = (MovableObject)0x0;
  local_30[0x151] = (MovableObject)0x0;
  vector<>();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  vector<>();
  local_8._0_1_ = 7;
  vector<>();
  local_8._0_1_ = 8;
  vector<>();
  local_8._0_1_ = 9;
  *(undefined4 *)(local_30 + 400) = 0;
  *(undefined4 *)(local_30 + 0x194) = 0;
  vector<>();
  local_8._0_1_ = 10;
  vector<>();
  local_8._0_1_ = 0xb;
  FUN_0083ead2(local_30 + 0x1b0,0xc,2,vector<>,FUN_0041fe20);
  local_8._0_1_ = 0xc;
  *(undefined4 *)(local_30 + 0x1c8) = 0;
  *(undefined4 *)(local_30 + 0x1cc) = 0;
  *(undefined4 *)(local_30 + 0x1d0) = 0;
  *(undefined4 *)(local_30 + 0x1d4) = 0;
  *(undefined4 *)(local_30 + 0x1d8) = 0;
  local_30[0x1dc] = (MovableObject)0x0;
  Ogre::MovableObject::setCastShadows(local_30,false);
  FUN_004bae50(0x400);
  FUN_004bae50(0x400);
  FUN_004bae50(0x400);
  FUN_004bae50(2);
  local_3c = Ogre::HardwareBufferManager::getSingletonPtr();
  uVar1 = (**(code **)(*(int *)local_3c + 0x34))();
  *(undefined4 *)(local_30 + 0x148) = uVar1;
  basic_string<>("Untextured");
  local_8._0_1_ = 0xd;
  pbVar6 = local_2c;
  pbVar5 = local_4c;
  this = Ogre::MaterialManager::getSingleton();
  local_44 = Ogre::MaterialManager::getByName(this,pbVar5,pbVar6);
  local_8._0_1_ = 0xe;
  local_40 = local_44;
  FUN_00449910(local_44);
  local_8._0_1_ = 0xd;
  FUN_004499a0();
  local_8 = CONCAT31(local_8._1_3_,0xc);
  ~basic_string<>();
  if (local_30 == (MovableObject *)0x0) {
    local_38 = (MovableObject *)0x0;
  }
  else {
    local_38 = local_30 + 0xd0;
  }
  this_00 = Ogre::Root::getSingleton();
  local_34 = Ogre::Root::getRenderSystem(this_00);
  (**(code **)(*(int *)local_34 + 0x1f8))(local_38);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

