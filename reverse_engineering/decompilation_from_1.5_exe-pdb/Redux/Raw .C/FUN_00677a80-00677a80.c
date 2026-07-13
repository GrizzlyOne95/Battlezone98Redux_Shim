
undefined4 FUN_00677a80(Renderable *param_1,Renderable *param_2)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  
  if ((param_1[0x30] == (Renderable)0x0) || (param_2[0x30] == (Renderable)0x0)) {
    uVar4 = 0;
  }
  else if (param_1[0xac] == param_2[0xac]) {
    cVar1 = FUN_0067b990(param_1 + 0x3c,param_2 + 0x3c);
    if (cVar1 == '\0') {
      if (*(int *)(param_1 + 0x94) == *(int *)(param_2 + 0x94)) {
        bVar2 = Ogre::Renderable::getUseIdentityProjection(param_1);
        bVar3 = Ogre::Renderable::getUseIdentityProjection(param_2);
        if (bVar2 == bVar3) {
          bVar2 = Ogre::Renderable::getUseIdentityView(param_1);
          bVar3 = Ogre::Renderable::getUseIdentityView(param_2);
          if (bVar2 == bVar3) {
            uVar4 = 1;
          }
          else {
            uVar4 = 0;
          }
        }
        else {
          uVar4 = 0;
        }
      }
      else {
        uVar4 = 0;
      }
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

