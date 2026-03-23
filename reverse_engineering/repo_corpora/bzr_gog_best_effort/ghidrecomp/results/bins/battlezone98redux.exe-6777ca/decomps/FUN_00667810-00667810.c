
void * __thiscall FUN_00667810(void *param_1,uint param_2)

{
  FUN_00668720();
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_delete(param_1);
  }
  return param_1;
}

