
void FUN_00663800(char param_1,undefined4 param_2,char *param_3)

{
  bool bVar1;
  Root *this;
  RenderSystem *pRVar2;
  Viewport *this_00;
  Camera *this_01;
  SceneManager *this_02;
  IlluminationRenderStage IVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 extraout_var;
  char local_18;
  
  if (param_1 != 'd') {
    return;
  }
  this = Ogre::Root::getSingletonPtr();
  uVar6 = extraout_var;
  pRVar2 = Ogre::Root::getRenderSystem(this);
  this_00 = (Viewport *)(**(code **)(*(int *)pRVar2 + 0x11c))(uVar6);
  if (this_00 != (Viewport *)0x0) {
    this_01 = Ogre::Viewport::getCamera(this_00);
    this_02 = Ogre::Camera::getSceneManager(this_01);
    bVar1 = Ogre::Viewport::getOverlaysEnabled(this_00);
    if ((bVar1) || (IVar3 = Ogre::SceneManager::_getCurrentRenderStage(this_02), IVar3 == 1)) {
      local_18 = '\0';
    }
    else {
      local_18 = '\x01';
    }
    *param_3 = local_18;
    if (((*param_3 == '\0') && (iVar4 = FUN_0044d2a0(), *(Viewport **)(iVar4 + 0x1c) == this_00)) &&
       (piVar5 = (int *)FUN_00685470(), piVar5 != (int *)0x0)) {
      uVar6 = (**(code **)(*(int *)this_02 + 0x31c))();
      (**(code **)(*piVar5 + 0x80))(uVar6);
    }
    return;
  }
  return;
}

