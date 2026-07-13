
void __thiscall FUN_0067d040(undefined4 param_1,SceneNode *param_2)

{
  SceneManager *pSVar1;
  
  if (param_2 != (SceneNode *)0x0) {
    FUN_0067cfa0(param_2,param_1);
    (**(code **)(*(int *)param_2 + 0x168))();
    pSVar1 = Ogre::SceneNode::getCreator(param_2);
    (**(code **)(*(int *)pSVar1 + 0x15c))(param_2);
  }
  return;
}

