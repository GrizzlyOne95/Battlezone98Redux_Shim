
void FUN_0067dd60(Light *param_1)

{
  int iVar1;
  float10 fVar2;
  float local_18;
  float local_14;
  float local_10;
  float local_8;
  
  iVar1 = FUN_00787ac0("NormalView","carAmbient",0x37,&DAT_02cc40c0);
  local_8 = (float)iVar1 / 100.0;
  Ogre::ColourValue::ColourValue((ColourValue *)&local_18,1.0,1.0,1.0,1.0);
  fVar2 = (float10)FUN_00787b60("Sun_Ambient",&DAT_00892a18,local_8,&DAT_02cc40c0);
  local_18 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Ambient","Green",local_8,&DAT_02cc40c0);
  local_14 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Ambient",&DAT_00892874,local_8,&DAT_02cc40c0);
  local_10 = (float)fVar2;
  Ogre::SceneManager::setAmbientLight(*(SceneManager **)(DAT_00920ea0 + 8),(ColourValue *)&local_18)
  ;
  fVar2 = (float10)FUN_00787b60("Sun_Diffuse",&DAT_00892a18,1.0 - local_8,&DAT_02cc40c0);
  local_18 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Diffuse","Green",1.0 - local_8,&DAT_02cc40c0);
  local_14 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Diffuse",&DAT_00892874,1.0 - local_8,&DAT_02cc40c0);
  local_10 = (float)fVar2;
  Ogre::Light::setDiffuseColour(param_1,(ColourValue *)&local_18);
  fVar2 = (float10)FUN_00787b60("Sun_Specular",&DAT_00892a18,local_18,&DAT_02cc40c0);
  local_18 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Specular","Green",local_14,&DAT_02cc40c0);
  local_14 = (float)fVar2;
  fVar2 = (float10)FUN_00787b60("Sun_Specular",&DAT_00892874,local_10,&DAT_02cc40c0);
  local_10 = (float)fVar2;
  Ogre::Light::setSpecularColour(param_1,(ColourValue *)&local_18);
  return;
}

