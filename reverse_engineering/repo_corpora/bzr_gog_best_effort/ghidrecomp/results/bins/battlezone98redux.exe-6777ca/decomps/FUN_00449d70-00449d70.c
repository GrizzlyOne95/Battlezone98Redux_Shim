
void __fastcall FUN_00449d70(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)**(undefined4 **)(param_1 + 4))(0);
    Ogre::StdAllocPolicy::deallocateBytes(*(void **)(param_1 + 4));
  }
  return;
}

