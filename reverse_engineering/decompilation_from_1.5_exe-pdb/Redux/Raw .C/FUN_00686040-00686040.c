
ManualObject * __thiscall FUN_00686040(ManualObject *param_1,uint param_2)

{
  Ogre::ManualObject::~ManualObject(param_1);
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_delete(param_1);
  }
  return param_1;
}

