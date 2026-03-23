
DefaultShadowCameraSetup * __thiscall FUN_006815e0(DefaultShadowCameraSetup *param_1,uint param_2)

{
  Ogre::DefaultShadowCameraSetup::~DefaultShadowCameraSetup(param_1);
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<3>_>::operator_delete(param_1);
  }
  return param_1;
}

