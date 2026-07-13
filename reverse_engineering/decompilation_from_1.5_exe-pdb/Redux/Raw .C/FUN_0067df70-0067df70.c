
void FUN_0067df70(void)

{
  Vector3 local_38 [12];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00680fe0(local_14);
  Ogre::Vector3::Vector3(local_38,-(float)DAT_02ceb830,-(float)DAT_02ceb834,DAT_02ceb838);
  basic_string<>("terrain_masterlight");
  local_8 = 0;
  DAT_00920ca0 = (Light *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x120))(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>();
  Ogre::Light::setType(DAT_00920ca0,1);
  FUN_0067dd60(DAT_00920ca0);
  Ogre::Light::setDirection(DAT_00920ca0,local_38);
  Ogre::MovableObject::setCastShadows((MovableObject *)DAT_00920ca0,true);
  Ogre::Light::setShadowFarDistance(DAT_00920ca0,128.0);
  Ogre::Light::setShadowNearClipDistance(DAT_00920ca0,0.0);
  Ogre::Light::setShadowFarClipDistance(DAT_00920ca0,320.0);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

