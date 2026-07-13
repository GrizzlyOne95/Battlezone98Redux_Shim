
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044cb70(float param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float local_4c;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined1 local_3c [4];
  undefined4 local_38;
  undefined4 *local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  float local_1c;
  float local_18;
  undefined1 local_14 [4];
  float local_10;
  int local_c;
  undefined4 *local_8;
  
  FUN_00447e20(local_14);
  while( true ) {
    iVar1 = FUN_00447e70();
    FUN_00447e50(local_3c);
    iVar2 = FUN_00447e70();
    if (iVar1 == iVar2) break;
    local_24 = (undefined4 *)FUN_00447e70();
    local_8 = local_24;
    FUN_00447e90();
    if (*(char *)(local_8 + 7) == '\0') {
      local_34 = local_8;
      local_20 = local_8;
      if (local_8 == (undefined4 *)0x0) {
        local_38 = 0;
      }
      else {
        local_38 = (**(code **)*local_8)(1);
      }
    }
    else {
      Ogre::Light::setPosition
                ((Light *)local_8[0x1c],(float)(*(double *)(local_8 + 0x12) - (double)_DAT_025f8e4c)
                 ,(float)(*(double *)(local_8 + 0x14) - (double)_DAT_025f8e50),
                 (float)(-*(double *)(local_8 + 0x16) - (double)_DAT_025f8e54));
      Ogre::Light::setDirection
                ((Light *)local_8[0x1c],(float)local_8[0xe],(float)local_8[0xf],
                 -(float)local_8[0x10]);
      fVar3 = (float10)FUN_00447ed0((float)local_8[0x18] * *(float *)(local_c + 0x178),0,0x3f800000)
      ;
      local_10 = (float)fVar3;
      fVar3 = (float10)FUN_00448e60(*(undefined4 *)(local_c + 0x14c),
                                    *(undefined4 *)(local_c + 0x15c),local_10);
      local_28 = (float)fVar3;
      fVar3 = (float10)FUN_00448e60(*(undefined4 *)(local_c + 0x150),
                                    *(undefined4 *)(local_c + 0x160),local_10);
      local_2c = (float)fVar3;
      fVar3 = (float10)FUN_00448e60(*(undefined4 *)(local_c + 0x154),
                                    *(undefined4 *)(local_c + 0x164),local_10);
      local_30 = (float)fVar3;
      fVar3 = (float10)FUN_00448e60(*(undefined4 *)(local_c + 0x158),
                                    *(undefined4 *)(local_c + 0x168),local_10);
      local_18 = (float)fVar3;
      fVar3 = (float10)FUN_00448e60(*(undefined4 *)(local_c + 0x16c),
                                    *(undefined4 *)(local_c + 0x170),local_10);
      local_1c = (float)fVar3;
      Ogre::ColourValue::ColourValue((ColourValue *)&local_4c,1.0,1.0,1.0,1.0);
      local_4c = local_28 * local_18;
      local_48 = local_2c * local_18;
      local_44 = local_30 * local_18;
      local_40 = 0x3f800000;
      Ogre::Light::setAttenuation
                ((Light *)local_8[0x1c],local_1c,1.0,0.0,15.0 / (local_1c * local_1c));
      Ogre::Light::setDiffuseColour((Light *)local_8[0x1c],local_4c,local_48,local_44);
      Ogre::Light::setSpecularColour((Light *)local_8[0x1c],local_4c,local_48,local_44);
      local_8[0x18] = (float)local_8[0x18] + param_1;
    }
  }
  return;
}

