
void FUN_0067ed9d(void)

{
  SkeletonInstance *pSVar1;
  undefined4 uVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + -0x6c) != 0) {
    pSVar1 = Ogre::Entity::getSkeleton(*(Entity **)(unaff_EBP + -0x6c));
    *(SkeletonInstance **)(unaff_EBP + -0x80) = pSVar1;
    uVar2 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    *(undefined4 *)(unaff_EBP + -0x78) = uVar2;
    uVar2 = (**(code **)(**(int **)(unaff_EBP + -0x78) + 0x180))(ZERO_exref,IDENTITY_exref);
    *(undefined4 *)(unaff_EBP + -0x70) = uVar2;
    (**(code **)(**(int **)(unaff_EBP + -0x70) + 0x124))(*(undefined4 *)(unaff_EBP + -0x6c));
    *(undefined4 *)(*(int *)(unaff_EBP + -0x68) + 0xcc) = *(undefined4 *)(unaff_EBP + -0x6c);
    *(undefined4 *)(*(int *)(unaff_EBP + -0x68) + 0xd0) = *(undefined4 *)(unaff_EBP + -0x70);
    *(undefined4 *)(*(int *)(unaff_EBP + -0x68) + 0xd4) = *(undefined4 *)(unaff_EBP + -0x80);
    Ogre::MovableObject::setCastShadows(*(MovableObject **)(unaff_EBP + -0x6c),true);
    (**(code **)(**(int **)(unaff_EBP + -0x70) + 0x38))(0xbf800000,0x3f800000,0xbf800000);
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

