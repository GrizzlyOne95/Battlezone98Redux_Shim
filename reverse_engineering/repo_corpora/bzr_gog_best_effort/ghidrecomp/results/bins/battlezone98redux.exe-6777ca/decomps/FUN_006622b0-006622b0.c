
void __fastcall FUN_006622b0(undefined4 *param_1)

{
  uint uVar1;
  int *piVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084db38;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = SubEntityTransparencyMaterial::vftable;
  local_8 = 0;
  piVar2 = (int *)get(uVar1);
  pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           AUTODETECT_RESOURCE_GROUP_NAME_exref;
  pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           (**(code **)(*piVar2 + 0x58))();
  Ogre::SubEntity::setMaterialName((SubEntity *)param_1[7],pbVar3,pbVar4);
  local_8 = 0xffffffff;
  FUN_00661a50();
  ExceptionList = local_10;
  return;
}

