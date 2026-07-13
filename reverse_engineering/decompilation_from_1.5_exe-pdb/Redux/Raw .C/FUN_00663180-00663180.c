
Technique * __thiscall FUN_00663180(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  Material *this;
  Technique *pTVar2;
  ushort uVar3;
  
  cVar1 = FUN_00427270(param_3,&DAT_00892124,param_1);
  if (cVar1 == '\0') {
    pTVar2 = (Technique *)0x0;
  }
  else {
    uVar3 = 0;
    this = (Material *)get();
    pTVar2 = Ogre::Material::getTechnique(this,uVar3);
  }
  return pTVar2;
}

