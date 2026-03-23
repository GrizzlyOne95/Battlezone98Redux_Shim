
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00683370(float param_1,float param_2,float param_3,float param_4,float param_5)

{
  ColourValue *pCVar1;
  undefined4 *puVar2;
  float fVar3;
  ColourValue local_24 [16];
  ColourValue local_14 [16];
  
  fVar3 = 0.0;
  pCVar1 = (ColourValue *)Ogre::ColourValue::ColourValue(local_14,param_1,param_2,param_3,1.0);
  Ogre::SceneManager::setFog(*(SceneManager **)(DAT_00920ea0 + 8),3,pCVar1,fVar3,param_4,param_5);
  puVar2 = (undefined4 *)Ogre::ColourValue::ColourValue(local_24,param_1,param_2,param_3,1.0);
  _DAT_025f8ea8 = *puVar2;
  _DAT_025f8eac = puVar2[1];
  _DAT_025f8eb0 = puVar2[2];
  _DAT_025f8eb4 = puVar2[3];
  return;
}

