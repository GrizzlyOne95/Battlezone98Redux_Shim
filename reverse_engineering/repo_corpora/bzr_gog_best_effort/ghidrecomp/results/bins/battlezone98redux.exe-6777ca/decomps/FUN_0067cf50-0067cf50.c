
float10 FUN_0067cf50(void)

{
  char cVar1;
  Root *this;
  RenderSystem *pRVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  this = Ogre::Root::getSingleton();
  pRVar2 = Ogre::Root::getRenderSystem(this);
  uVar3 = (**(code **)(*(int *)pRVar2 + 4))("Direct3D9 Rendering Subsystem");
  cVar1 = FUN_00427270(uVar3);
  if (cVar1 == '\0') {
    fVar4 = (float10)0;
  }
  else {
    fVar4 = (float10)0.5;
  }
  return fVar4;
}

