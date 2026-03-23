
void * __thiscall FUN_00669b10(void *param_1,uint param_2)

{
  FUN_00669b40();
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_delete(param_1);
  }
  return param_1;
}

