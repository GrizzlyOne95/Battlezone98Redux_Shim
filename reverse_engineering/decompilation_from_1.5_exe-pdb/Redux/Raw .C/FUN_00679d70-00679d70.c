
void FUN_00679d70(undefined4 param_1,int param_2,float param_3)

{
  char cVar1;
  bool bVar2;
  char cVar3;
  float *pfVar4;
  undefined4 local_c;
  int *local_8;
  
  local_c = 0;
  pfVar4 = (float *)FUN_0067ba40(&param_3,&local_c);
  param_3 = *pfVar4;
  if ((((local_8[0x72] != 0) && (*(int *)(local_8[0x72] + 0x94) == param_2)) &&
      (*(float *)(local_8[0x72] + 0xb0) == param_3 * param_3)) &&
     (((cVar1 = FUN_0067b990(local_8[0x72] + 0x3c,param_1), cVar1 == '\0' &&
       (bVar2 = Ogre::Renderable::getUseIdentityProjection((Renderable *)local_8[0x72]),
       bVar2 == (bool)(char)local_8[0x54])) &&
      ((bVar2 = Ogre::Renderable::getUseIdentityView((Renderable *)local_8[0x72]),
       bVar2 == (bool)*(char *)((int)local_8 + 0x151) &&
       (cVar1 = *(char *)(local_8[0x72] + 0xac), cVar3 = (**(code **)(*local_8 + 0xb0))(),
       cVar1 == cVar3)))))) {
    return;
  }
  FUN_00679830(0);
  FUN_00679ac0(param_1,param_2,param_3 * param_3);
  return;
}

