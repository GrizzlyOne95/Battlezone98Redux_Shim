
void FUN_0077924c(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  Mesh *this;
  int unaff_EBP;
  AxisAlignedBox *pAVar4;
  bool bVar5;
  
  *(undefined4 *)(unaff_EBP + -4) = 4;
  (**(code **)(**(int **)(unaff_EBP + -0x34) + 4))(2,unaff_EBP + -0x84);
  FUN_0077c670();
  cVar1 = FUN_0077c010();
  if (cVar1 != '\0') {
    FUN_0077c670();
    FUN_0077c030();
  }
  **(undefined1 **)(unaff_EBP + -0x44) = 1;
  iVar2 = FUN_0077c670();
  Ogre::HardwareIndexBufferSharedPtr::operator=
            (*(HardwareIndexBufferSharedPtr **)(*(int *)(unaff_EBP + -0x44) + 0xc),
             (HardwareIndexBufferSharedPtr *)(iVar2 + 0xc));
  FUN_0077c670();
  uVar3 = FUN_0041c1d0();
  *(undefined4 *)(*(int *)(*(int *)(unaff_EBP + -0x44) + 0xc) + 0xc) = uVar3;
  *(undefined4 *)(*(int *)(*(int *)(unaff_EBP + -0x44) + 0xc) + 8) = 0;
  uVar3 = Ogre::AxisAlignedBox::AxisAlignedBox
                    ((AxisAlignedBox *)(unaff_EBP + -0xe8),
                     *(float *)(*(int *)(unaff_EBP + -0x24) + 0x280 +
                                *(int *)(unaff_EBP + 0xc) * 0x40 + *(int *)(unaff_EBP + 0x10) * 0x10
                               ) -
                     *(float *)(*(int *)(unaff_EBP + -0x24) + 0x100 +
                                *(int *)(unaff_EBP + 0xc) * 0x30 + *(int *)(unaff_EBP + 0x10) * 0xc)
                     ,*(float *)(*(int *)(unaff_EBP + -0x24) + 0x1c0 +
                                 *(int *)(unaff_EBP + 0xc) * 0x10 + *(int *)(unaff_EBP + 0x10) * 4)
                      - *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x30 +
                                   0x104 + *(int *)(unaff_EBP + 0x10) * 0xc),
                     *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x40 +
                                0x284 + *(int *)(unaff_EBP + 0x10) * 0x10) -
                     *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x30 +
                                0x108 + *(int *)(unaff_EBP + 0x10) * 0xc),
                     *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x40 +
                                0x288 + *(int *)(unaff_EBP + 0x10) * 0x10) -
                     *(float *)(*(int *)(unaff_EBP + -0x24) + 0x100 +
                                *(int *)(unaff_EBP + 0xc) * 0x30 + *(int *)(unaff_EBP + 0x10) * 0xc)
                     ,*(float *)(*(int *)(unaff_EBP + -0x24) + 0x200 +
                                 *(int *)(unaff_EBP + 0xc) * 0x10 + *(int *)(unaff_EBP + 0x10) * 4)
                      - *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x30 +
                                   0x104 + *(int *)(unaff_EBP + 0x10) * 0xc),
                     *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x40 +
                                0x28c + *(int *)(unaff_EBP + 0x10) * 0x10) -
                     *(float *)(*(int *)(unaff_EBP + -0x24) + *(int *)(unaff_EBP + 0xc) * 0x30 +
                                0x108 + *(int *)(unaff_EBP + 0x10) * 0xc));
  *(undefined4 *)(unaff_EBP + -0xa4) = uVar3;
  *(undefined4 *)(unaff_EBP + -0xac) = *(undefined4 *)(unaff_EBP + -0xa4);
  *(undefined1 *)(unaff_EBP + -4) = 7;
  bVar5 = false;
  pAVar4 = *(AxisAlignedBox **)(unaff_EBP + -0xac);
  this = (Mesh *)get();
  Ogre::Mesh::_setBounds(this,pAVar4,bVar5);
  *(undefined1 *)(unaff_EBP + -4) = 4;
  Ogre::AxisAlignedBox::~AxisAlignedBox((AxisAlignedBox *)(unaff_EBP + -0xe8));
  free(*(void **)(unaff_EBP + -100));
  free(*(void **)(unaff_EBP + -0x60));
  *(undefined4 *)(*(int *)(unaff_EBP + -0x24) + 0x3a8) = 0;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x24) + 0x3ac) = 0;
  *(undefined1 *)(unaff_EBP + -4) = 1;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr
            ((HardwareVertexBufferSharedPtr *)(unaff_EBP + -0x84));
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  Ogre::HardwareVertexBufferSharedPtr::~HardwareVertexBufferSharedPtr
            ((HardwareVertexBufferSharedPtr *)(unaff_EBP + -0x8c));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

