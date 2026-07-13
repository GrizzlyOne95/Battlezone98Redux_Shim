
void __fastcall FUN_006786f0(int param_1)

{
  int iVar1;
  char cVar2;
  wchar_t *pwVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f330;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  cVar2 = FUN_0041fc90();
  if (cVar2 == '\0') {
    pwVar3 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)(param_1 + 0x198));
    iVar1 = *(int *)pwVar3;
    local_8 = 0;
    if (*(int *)(iVar1 + 0x24) != 0) {
      (**(code **)**(undefined4 **)(iVar1 + 0x24))(iVar1);
    }
    FUN_00678779();
    return;
  }
  FUN_0041ff50();
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  *(undefined4 *)(param_1 + 400) = 0;
  *(undefined4 *)(param_1 + 0x194) = 0;
  *(undefined4 *)(param_1 + 0x1d4) = 0;
  *(undefined4 *)(param_1 + 0x1d8) = 0;
  *(undefined1 *)(param_1 + 0x1dc) = 0;
  FUN_004bb060();
  Ogre::AxisAlignedBox::operator=
            ((AxisAlignedBox *)(param_1 + 0xdc),(AxisAlignedBox *)BOX_NULL_exref);
  *(undefined4 *)(param_1 + 0xfc) = 0;
  ExceptionList = local_10;
  return;
}

