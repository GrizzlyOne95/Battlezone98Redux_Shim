
void __thiscall FUN_00662340(int param_1,undefined4 param_2)

{
  int *piVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  
  FUN_00661ac0(param_2);
  if (*(float *)(param_1 + 0x14) <= 0.001) {
    piVar1 = (int *)get();
    pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             AUTODETECT_RESOURCE_GROUP_NAME_exref;
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar1 + 0x58))();
    Ogre::SubEntity::setMaterialName(*(SubEntity **)(param_1 + 0x1c),pbVar2,pbVar3);
  }
  else {
    piVar1 = (int *)get();
    pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             AUTODETECT_RESOURCE_GROUP_NAME_exref;
    pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*piVar1 + 0x58))();
    Ogre::SubEntity::setMaterialName(*(SubEntity **)(param_1 + 0x1c),pbVar2,pbVar3);
  }
  return;
}

