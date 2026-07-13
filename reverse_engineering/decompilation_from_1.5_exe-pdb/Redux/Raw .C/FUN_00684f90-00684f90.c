
MovableObject * FUN_00684f90(undefined4 param_1,undefined4 param_2)

{
  void *pvVar1;
  int *piVar2;
  int *piVar3;
  MovableObject *local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f92c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<4>_>::operator_new(0x1e0);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = (MovableObject *)0x0;
  }
  else {
    local_20 = (MovableObject *)FUN_00677c20(param_1);
  }
  local_8 = 0xffffffff;
  Ogre::MovableObject::setCastShadows(local_20,false);
  FUN_006781a0(0,2,1,0);
  FUN_006781a0(0xc,4,5,0);
  FUN_006781a0(0x10,1,7,0);
  FUN_00684bd0(0x18);
  (**(code **)(*(int *)local_20 + 200))(param_2);
  piVar2 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x154))(param_1);
  (**(code **)(*piVar2 + 0x124))(local_20);
  piVar3 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
  (**(code **)(*piVar3 + 0x8c))(piVar2);
  ExceptionList = local_10;
  return local_20;
}

