
void FUN_0056fa50(void)

{
  char *pcVar1;
  int iVar2;
  uint uStack_b4;
  Image local_a4 [44];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined1 *local_6c;
  undefined4 local_68;
  uchar *local_64;
  uint local_60;
  undefined4 local_58;
  undefined4 local_54;
  char *local_50;
  uchar *local_4c;
  uint local_48;
  undefined2 local_44;
  undefined2 local_3e;
  int local_3c;
  char *local_38;
  char local_31;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b694;
  local_10 = ExceptionList;
  uStack_b4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_b4;
  ExceptionList = &local_10;
  local_18 = uStack_b4;
  local_44 = FUN_00572d90();
  local_3c = FUN_005771b0(local_44);
  if (local_3c == 0) {
    FUN_0056fc23();
    return;
  }
  local_58 = FUN_00575510(0xd);
  iVar2 = FUN_004bb390();
  if (iVar2 != 0) {
    FUN_0056fc23();
    return;
  }
  local_38 = &DAT_00917fac;
  local_6c = &DAT_00917fad;
  pcVar1 = local_38;
  do {
    local_38 = pcVar1;
    local_31 = *local_38;
    pcVar1 = local_38 + 1;
  } while (local_31 != '\0');
  local_50 = local_38 + -0x917fac;
  local_38 = pcVar1;
  if (local_50 == (char *)0x0) {
    FUN_0056fc23();
    return;
  }
  local_8 = 0;
  local_74 = Ogre::Image::Image(local_a4);
  local_8._0_1_ = 1;
  local_78 = basic_string<>(&DAT_00917fac);
  local_8._0_1_ = 2;
  Ogre::Image::load(local_a4,local_30,
                    (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    AUTODETECT_RESOURCE_GROUP_NAME_exref);
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_64 = Ogre::Image::getData(local_a4);
  local_4c = local_64;
  local_60 = Ogre::Image::getSize(local_a4);
  local_48 = local_60;
  FUN_00575810(local_4c,local_60);
  local_68 = FUN_00764760();
  local_3e = FUN_00747070();
  local_70 = FUN_005771b0(local_3e);
  local_54 = local_70;
  FUN_00575570(0xd,local_4c,local_48);
  local_8 = (uint)local_8._1_3_ << 8;
  Ogre::Image::~Image(local_a4);
  FUN_0056fc13();
  return;
}

