
void * __thiscall FUN_00677fa0(void *param_1,uint param_2)

{
  FUN_00677fd0();
  if ((param_2 & 1) != 0) {
    Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_delete(param_1);
  }
  return param_1;
}

