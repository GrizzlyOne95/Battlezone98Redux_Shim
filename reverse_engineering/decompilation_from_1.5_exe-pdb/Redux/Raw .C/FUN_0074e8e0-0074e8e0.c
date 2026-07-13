
void FUN_0074e8e0(void)

{
  int iVar1;
  uint uStack_1b4;
  undefined1 auStack_e4 [160];
  undefined4 local_44;
  basic_ostream<char,struct_std::char_traits<char>_> *local_40;
  undefined8 local_3c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_34;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_30;
  undefined4 local_2c;
  undefined1 *local_24;
  int local_20;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bf36;
  local_10 = ExceptionList;
  uStack_1b4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_1b4;
  ExceptionList = &local_10;
  iVar1 = FUN_00764870();
  if ((iVar1 != 0) && (*(int *)(local_20 + 0x54) == 0)) {
    local_3c = FUN_00822ea0();
    *(undefined8 *)(local_20 + 0x80) = local_3c;
    local_18 = (int *)FUN_0074db30();
    if (local_18 != (int *)0x0) {
      local_8 = 0;
      (**(code **)(*local_18 + 0xc))("GameVersion",PTR_s_2_2_301_008eda3c,0);
      local_44 = FUN_00574400(3,1);
      local_8._0_1_ = 1;
      if (&stack0x00000000 == (undefined1 *)0xf4) {
        local_24 = (undefined1 *)0x0;
      }
      else {
        local_24 = auStack_e4;
      }
      local_40 = (basic_ostream<char,struct_std::char_traits<char>_> *)
                 FUN_004bc590(local_24,"CGalaxyLobby::GetLobbyList called, requesting lobbies");
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_40,FUN_004bc8c0);
      local_30 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      local_2c = FUN_0081e820();
      local_34 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_34,local_30);
      (**(code **)(*local_18 + 8))(0);
      *(undefined4 *)(local_20 + 0x54) = 1;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00417f10();
      FUN_0074eb17();
      return;
    }
  }
  ExceptionList = local_10;
  return;
}

