
void __thiscall FUN_00678880(int param_1,Camera *param_2)

{
  uint uVar1;
  int *piVar2;
  Vector3 *pVVar3;
  Quaternion *pQVar4;
  AxisAlignedBox *pAVar5;
  float10 fVar6;
  
  uVar1 = (**(code **)(*(int *)param_2 + 0xd4))();
  if ((uVar1 & *(uint *)(param_1 + -0x80)) != 0) {
    piVar2 = (int *)(**(code **)(*(int *)(param_1 + -0xd4) + 0x54))();
    if (piVar2 != (int *)0x0) {
      pVVar3 = Ogre::Camera::getDerivedPosition(param_2);
      (**(code **)(*piVar2 + 0x30))(pVVar3);
      pQVar4 = Ogre::Camera::getDerivedOrientation(param_2);
      (**(code **)(*piVar2 + 0x24))(pQVar4);
    }
    pAVar5 = (AxisAlignedBox *)(**(code **)(*(int *)param_2 + 0x74))();
    Ogre::AxisAlignedBox::operator=((AxisAlignedBox *)(param_1 + 8),pAVar5);
    fVar6 = (float10)(**(code **)(*(int *)param_2 + 0x14c))();
    *(float *)(param_1 + 0x28) = (float)fVar6;
    (**(code **)(*(int *)(param_2 + 0xd0) + 0x18))(param_1 + 0x2c);
  }
  return;
}

