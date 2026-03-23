
void FUN_00680870(int param_1)

{
  SceneNode *this;
  int *piVar1;
  SceneManager *pSVar2;
  
  if ((*(int *)(param_1 + 200) != 0) && (*(int *)(param_1 + 0xc0) != 0)) {
    this = *(SceneNode **)(param_1 + 200);
    (**(code **)(*(int *)this + 0x138))(*(int *)(param_1 + 0xc0));
    piVar1 = (int *)(**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    (**(code **)(*piVar1 + 0xa8))(this);
    pSVar2 = Ogre::SceneNode::getCreator(this);
    (**(code **)(*(int *)pSVar2 + 0x15c))(this);
    *(undefined4 *)(param_1 + 200) = 0;
  }
  return;
}

