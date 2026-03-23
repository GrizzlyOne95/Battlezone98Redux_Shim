
void FUN_0067ce80(void)

{
  Quaternion *pQVar1;
  undefined1 *puVar2;
  float fVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  float local_8;
  
  if (DAT_00920e98 != (int *)0x0) {
    local_8 = DAT_00920e90;
    if (DAT_00920e90 <= 1e-05) {
      local_8 = 0.002;
    }
    uVar5 = 0x3c888889;
    puVar4 = local_10;
    puVar2 = local_14;
    fVar3 = local_8;
    FUN_0044c7a0(0x3f800000);
    FUN_00662dc0(puVar2,fVar3);
    uVar5 = FUN_0067c7f0(puVar4,uVar5);
    FUN_00662df0(uVar5);
    (**(code **)(*DAT_00920e98 + 0x74))(local_c,0);
    pQVar1 = (Quaternion *)(**(code **)(*DAT_00920e98 + 0x1c))();
    Ogre::Quaternion::operator=((Quaternion *)&DAT_025f8e70,pQVar1);
  }
  return;
}

