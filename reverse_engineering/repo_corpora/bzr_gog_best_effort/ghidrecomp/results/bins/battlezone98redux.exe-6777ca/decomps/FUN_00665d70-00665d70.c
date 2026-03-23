
Root * __thiscall FUN_00665d70(Root *param_1,uint param_2)

{
  Ogre::Root::~Root(param_1);
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_delete(param_1);
  }
  return param_1;
}

