
void FUN_00678779(void)

{
  char cVar1;
  wchar_t *pwVar2;
  int unaff_EBP;
  int iVar3;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  FUN_004f9080(0);
  *(undefined4 *)(*(int *)(unaff_EBP + -0x18) + 0x4c) = 0;
  Ogre::SharedPtr<class_Ogre::HardwareIndexBuffer>::setNull
            ((SharedPtr<class_Ogre::HardwareIndexBuffer> *)(*(int *)(unaff_EBP + -0x18) + 0x7c));
  FUN_004cbb80();
  iVar3 = unaff_EBP + -0x18;
  FUN_00677a60(iVar3);
  FUN_0041fe40(iVar3);
  cVar1 = FUN_0041fc90();
  if (cVar1 == '\0') {
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)(*(int *)(unaff_EBP + -0x14) + 0x198));
    *(undefined4 *)(unaff_EBP + -0x18) = *(undefined4 *)pwVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (*(int *)(*(int *)(unaff_EBP + -0x18) + 0x24) != 0) {
      (**(code **)**(undefined4 **)(*(int *)(unaff_EBP + -0x18) + 0x24))
                (*(undefined4 *)(unaff_EBP + -0x18));
    }
    FUN_00678779();
    return;
  }
  FUN_0041ff50();
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1c8) = 0;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 400) = 0;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x194) = 0;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1d4) = 0;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0x1d8) = 0;
  *(undefined1 *)(*(int *)(unaff_EBP + -0x14) + 0x1dc) = 0;
  FUN_004bb060();
  Ogre::AxisAlignedBox::operator=
            ((AxisAlignedBox *)(*(int *)(unaff_EBP + -0x14) + 0xdc),(AxisAlignedBox *)BOX_NULL_exref
            );
  *(undefined4 *)(*(int *)(unaff_EBP + -0x14) + 0xfc) = 0;
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

