
void FUN_0067d180(undefined4 param_1)

{
  ColourValue *pCVar1;
  uint uStack_158;
  ColourValue local_148 [16];
  ColourValue local_138 [16];
  Quaternion local_128 [16];
  Vector3 local_118 [24];
  undefined4 local_100;
  undefined4 local_f8;
  undefined1 local_d9;
  undefined1 local_d0 [120];
  char local_58 [64];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f634;
  local_10 = ExceptionList;
  uStack_158 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_158;
  ExceptionList = &local_10;
  local_18 = uStack_158;
  Ogre::Quaternion::Quaternion(local_128);
  Ogre::Camera::setOrientation(*(Camera **)(DAT_00920ea0 + 0x18),local_128);
  local_d9 = DAT_00920e98 != 0;
  if ((bool)local_d9) {
    FUN_0067d090(DAT_00920e98);
    (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x198))();
    (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x140))();
  }
  DAT_00920ec0 = 0;
  DAT_00920e98 = 0;
  DAT_00920ca0 = (Light *)0x0;
  Ogre::Vector3::Vector3(local_118,-1.0,-1.0,-1.0);
  DAT_00920ca0 = (Light *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x11c))();
  Ogre::Light::setType(DAT_00920ca0,1);
  Ogre::Light::setDirection(DAT_00920ca0,local_118);
  pCVar1 = (ColourValue *)Ogre::ColourValue::ColourValue(local_138,0.3,0.3,0.3,1.0);
  Ogre::SceneManager::setAmbientLight(*(SceneManager **)(DAT_00920ea0 + 8),pCVar1);
  Ogre::Light::setDiffuseColour(DAT_00920ca0,2.0,2.0,2.0);
  pCVar1 = (ColourValue *)Ogre::ColourValue::ColourValue(local_148,0.4,0.4,0.4,1.0);
  Ogre::Light::setSpecularColour(DAT_00920ca0,pCVar1);
  Ogre::MovableObject::setCastShadows((MovableObject *)DAT_00920ca0,true);
  Ogre::Light::setShadowFarDistance(DAT_00920ca0,64.0);
  Ogre::Light::setShadowNearClipDistance(DAT_00920ca0,0.0);
  Ogre::Light::setShadowFarClipDistance(DAT_00920ca0,192.0);
  (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x38c))(0x43000000);
  sprintf(local_58,"%.*s.mesh",0x3a,param_1);
  local_8 = 0;
  local_100 = basic_string<>(local_58);
  local_8._0_1_ = 1;
  DAT_00920ec0 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x17c))(local_d0);
  local_8 = (uint)local_8._1_3_ << 8;
  local_f8 = DAT_00920ec0;
  ~basic_string<>();
  FUN_0067d4d3();
  return;
}

