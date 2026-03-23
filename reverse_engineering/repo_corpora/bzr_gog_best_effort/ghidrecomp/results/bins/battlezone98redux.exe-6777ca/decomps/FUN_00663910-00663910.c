
undefined4 FUN_00663910(undefined4 param_1)

{
  Radian *pRVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  float local_8;
  
  uVar4 = 0x40000000;
  bVar2 = false;
  uVar3 = param_1;
  pRVar1 = (Radian *)FUN_00662dc0(local_c,0x3f000000);
  local_8 = Ogre::Math::Tan(pRVar1,bVar2);
  Ogre::Math::ATan((float)local_10);
  FUN_00662dc0(uVar3,uVar4);
  return param_1;
}

