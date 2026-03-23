
void FUN_0067ccf0(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000010;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined1 *puVar2;
  undefined1 local_34 [4];
  undefined1 local_30 [8];
  undefined1 local_28 [16];
  float local_18;
  Radian local_14 [4];
  Radian local_10 [4];
  Radian local_c [4];
  Radian local_8 [4];
  
  Ogre::Camera::setPosition(*(Camera **)(DAT_00920ea0 + 0x18),0.0,1.0,DAT_008ed0dc);
  uVar1 = FUN_0044c7a0(in_stack_00000010);
  FUN_00662df0(uVar1);
  Ogre::Camera::roll(*(Camera **)(DAT_00920ea0 + 0x18),local_8);
  uVar1 = FUN_0044c7a0(in_stack_00000014);
  FUN_00662df0(uVar1);
  Ogre::Camera::pitch(*(Camera **)(DAT_00920ea0 + 0x18),local_c);
  uVar1 = FUN_0044c7a0(in_stack_00000018);
  FUN_00662df0(uVar1);
  Ogre::Camera::yaw(*(Camera **)(DAT_00920ea0 + 0x18),local_10);
  Ogre::Camera::setAutoAspectRatio(*(Camera **)(DAT_00920ea0 + 0x18),true);
  uVar1 = 0x3f000000;
  puVar2 = local_28;
  FUN_0044c7a0(0x42700000);
  uVar1 = FUN_00662dc0(puVar2,uVar1);
  FUN_00662df0(uVar1);
  uVar1 = 0x40000000;
  puVar2 = local_30;
  local_18 = Ogre::Math::Tan(local_14,false);
  Ogre::Math::ATan((float)local_34);
  uVar1 = FUN_00662dc0(puVar2,uVar1);
  (**(code **)(**(int **)(DAT_00920ea0 + 0x18) + 0x138))(uVar1);
  return;
}

