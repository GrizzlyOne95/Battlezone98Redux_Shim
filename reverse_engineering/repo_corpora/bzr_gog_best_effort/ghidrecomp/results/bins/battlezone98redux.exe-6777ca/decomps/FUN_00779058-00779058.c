
void FUN_00779058(void)

{
  undefined1 uVar1;
  uint uVar2;
  HardwareBufferManager *pHVar3;
  int iVar4;
  undefined4 uVar5;
  HardwareVertexBuffer *pHVar6;
  int unaff_EBP;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  *(undefined4 *)(unaff_EBP + -4) = 1;
  (**(code **)(**(int **)(unaff_EBP + -0x34) + 4))(1,unaff_EBP + -0x8c);
  *(undefined4 *)(unaff_EBP + -0x3c) = 0;
  (**(code **)(**(int **)(unaff_EBP + -0x28) + 4))(2,*(undefined4 *)(unaff_EBP + -0x3c),0,7,1);
  uVar2 = Ogre::VertexElement::getTypeSize(0);
  *(uint *)(unaff_EBP + -0x3c) = uVar2 + *(int *)(unaff_EBP + -0x3c);
  pHVar3 = Ogre::HardwareBufferManager::getSingleton();
  *(HardwareBufferManager **)(unaff_EBP + -0x78) = pHVar3;
  uVar9 = 2;
  iVar4 = get(2,0);
  uVar8 = *(undefined4 *)(*(int *)(iVar4 + 0x1b4) + 0x14);
  uVar7 = *(undefined4 *)(unaff_EBP + -0x3c);
  (**(code **)(**(int **)(unaff_EBP + -0x78) + 0x20))(unaff_EBP + -0x84,uVar7,uVar8);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  *(undefined1 *)(unaff_EBP + -4) = 5;
  uVar5 = FUN_0077c670();
  *(undefined4 *)(unaff_EBP + -0x90) = uVar5;
  uVar1 = FUN_00777710();
  *(undefined1 *)(unaff_EBP + -0x29) = uVar1;
  if (*(char *)(unaff_EBP + -0x29) == '\0') {
    *(undefined1 *)
     (*(int *)(unaff_EBP + -0x24) + 0x270 + *(int *)(unaff_EBP + 0xc) * 4 +
     *(int *)(unaff_EBP + 0x10)) = 1;
  }
  else {
    pHVar6 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)(unaff_EBP + -0x84));
    *(HardwareVertexBuffer **)(unaff_EBP + -0xa8) = pHVar6;
    *(undefined4 *)(unaff_EBP + -0x6c) = *(undefined4 *)(unaff_EBP + -0xa8);
    pHVar6 = Ogre::SharedPtr<class_Ogre::HardwareVertexBuffer>::operator->
                       ((SharedPtr<class_Ogre::HardwareVertexBuffer> *)(unaff_EBP + -0x84));
    *(HardwareVertexBuffer **)(unaff_EBP + -200) = pHVar6;
    uVar2 = Ogre::HardwareBuffer::getSizeInBytes(*(HardwareBuffer **)(unaff_EBP + -200));
    *(uint *)(unaff_EBP + -0xb0) = uVar2;
    (**(code **)(**(int **)(unaff_EBP + -0x6c) + 0x18))
              (0,*(undefined4 *)(unaff_EBP + -0xb0),*(undefined4 *)(unaff_EBP + -0x60),1);
  }
  FUN_0077924c(uVar7,uVar8,uVar9);
  return;
}

