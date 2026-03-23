
void __fastcall FUN_007d2870(int param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined1 *puStack_68;
  undefined1 local_58 [8];
  undefined1 *local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  MaterialManager *local_3c;
  int *local_38;
  undefined4 *local_34;
  int local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00862b20;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  if (*(int *)(param_1 + 0x140) != 0) {
    local_48 = *(undefined4 **)(param_1 + 0x140);
    local_34 = local_48;
    if (local_48 == (undefined4 *)0x0) {
      local_40 = 0;
    }
    else {
      puStack_68 = (undefined1 *)0x7d28d1;
      local_40 = (**(code **)*local_48)();
    }
    *(undefined4 *)(local_30 + 0x140) = 0;
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      local_38 = (int *)get();
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (**(code **)(*local_38 + 0x58))();
      puStack_68 = (undefined1 *)0x7d2926;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar2);
      local_8 = 0;
      FUN_004c85d0();
      local_3c = Ogre::MaterialManager::getSingleton();
      puStack_68 = (undefined1 *)0x7d2955;
      (**(code **)(*(int *)local_3c + 0x38))();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  puStack_68 = local_58;
  local_4c = FUN_007d3ff0();
  local_8 = 1;
  puStack_68 = (undefined1 *)0x7d2996;
  local_44 = local_4c;
  FUN_00449910();
  local_8 = 0xffffffff;
  FUN_004499a0();
  local_50 = (undefined1 *)&puStack_68;
  FUN_004498d0(local_30 + 0x114);
  FUN_007d2b70();
  *(uint *)(local_30 + 0x14) = *(uint *)(local_30 + 0x14) | 0x10;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

