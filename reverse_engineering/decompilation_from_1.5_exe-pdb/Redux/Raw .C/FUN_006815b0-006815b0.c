
PSSMShadowCameraSetup * __thiscall FUN_006815b0(PSSMShadowCameraSetup *param_1,uint param_2)

{
  Ogre::PSSMShadowCameraSetup::~PSSMShadowCameraSetup(param_1);
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<3>_>::operator_delete(param_1);
  }
  return param_1;
}

