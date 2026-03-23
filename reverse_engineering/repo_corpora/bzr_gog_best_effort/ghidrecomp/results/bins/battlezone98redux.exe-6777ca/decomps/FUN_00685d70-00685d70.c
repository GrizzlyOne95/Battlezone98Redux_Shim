
void FUN_00685d70(int *param_1)

{
  int *piVar1;
  SceneManager *pSVar2;
  
  if (*param_1 != 0) {
    piVar1 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    (**(code **)(*piVar1 + 0xa8))(*param_1);
    (**(code **)(*(int *)*param_1 + 0x168))();
    pSVar2 = Ogre::SceneNode::getCreator((SceneNode *)*param_1);
    (**(code **)(*(int *)pSVar2 + 0x15c))(*param_1);
    *param_1 = 0;
  }
  return;
}

