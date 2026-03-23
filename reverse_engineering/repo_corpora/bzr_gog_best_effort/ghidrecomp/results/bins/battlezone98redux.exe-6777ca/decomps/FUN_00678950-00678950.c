
bool FUN_00678950(Renderable *param_1,Renderable *param_2)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  
  if ((param_1 == (Renderable *)0x0) && (param_2 != (Renderable *)0x0)) {
    bVar1 = true;
  }
  else if (param_2 == (Renderable *)0x0) {
    bVar1 = false;
  }
  else if ((byte)param_1[0xac] < (byte)param_2[0xac]) {
    bVar1 = true;
  }
  else if ((byte)param_2[0xac] < (byte)param_1[0xac]) {
    bVar1 = false;
  }
  else if (*(float *)(param_1 + 0x34) < *(float *)(param_2 + 0x34) ||
           *(float *)(param_1 + 0x34) == *(float *)(param_2 + 0x34)) {
    if (*(float *)(param_2 + 0x34) < *(float *)(param_1 + 0x34) ||
        *(float *)(param_2 + 0x34) == *(float *)(param_1 + 0x34)) {
      if ((byte)param_1[0x31] < (byte)param_2[0x31]) {
        bVar1 = true;
      }
      else if ((byte)param_2[0x31] < (byte)param_1[0x31]) {
        bVar1 = false;
      }
      else {
        uVar3 = get();
        uVar4 = get();
        if (uVar3 < uVar4) {
          bVar1 = true;
        }
        else {
          uVar3 = get();
          uVar4 = get();
          if (uVar4 < uVar3) {
            bVar1 = false;
          }
          else if (*(int *)(param_1 + 0x94) < *(int *)(param_2 + 0x94)) {
            bVar1 = true;
          }
          else if (*(int *)(param_2 + 0x94) < *(int *)(param_1 + 0x94)) {
            bVar1 = false;
          }
          else {
            bVar1 = Ogre::Renderable::getUseIdentityProjection(param_1);
            bVar2 = Ogre::Renderable::getUseIdentityProjection(param_2);
            if (bVar1 < bVar2) {
              bVar1 = true;
            }
            else {
              bVar1 = Ogre::Renderable::getUseIdentityProjection(param_1);
              bVar2 = Ogre::Renderable::getUseIdentityProjection(param_2);
              if (bVar2 < bVar1) {
                bVar1 = false;
              }
              else {
                bVar1 = Ogre::Renderable::getUseIdentityView(param_1);
                bVar2 = Ogre::Renderable::getUseIdentityView(param_2);
                if (bVar1 < bVar2) {
                  bVar1 = true;
                }
                else {
                  bVar1 = Ogre::Renderable::getUseIdentityView(param_1);
                  bVar2 = Ogre::Renderable::getUseIdentityView(param_2);
                  if (bVar2 < bVar1) {
                    bVar1 = false;
                  }
                  else {
                    bVar1 = *(uint *)(param_1 + 0x2c) < *(uint *)(param_2 + 0x2c);
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

