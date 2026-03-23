
void FUN_007c65f0(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  Root *this;
  WindowEventListener *pWVar3;
  basic_ostream<char,struct_std::char_traits<char>_> local_f4 [152];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined4 local_48;
  undefined4 local_44;
  int *local_40;
  uint local_3c;
  int *local_38;
  WindowEventListener *local_34;
  FrameListener *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008620b3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_3c = 0;
  local_14 = uVar1;
  FUN_006ca050(2,1);
  local_8 = 0;
  basic_string<>("WINDOW");
  local_8._0_1_ = 1;
  iVar2 = FUN_0044d2a0(uVar1);
  local_40 = *(int **)(iVar2 + 0xc);
  (**(code **)(*local_40 + 0x6c))(local_2c,&local_3c);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_f4,local_3c);
  local_44 = param_1;
  local_48 = param_2;
  if (param_3 == 1) {
    iVar2 = FUN_00437570(&DAT_02cecee0,&local_44,&local_48);
    if (iVar2 != 0) {
      FUN_007c6290(local_44,local_48);
    }
  }
  iVar2 = FUN_0044d2a0();
  local_38 = *(int **)(iVar2 + 0xc);
  (**(code **)(*local_38 + 0x148))(local_50,local_5c,local_54,local_4c,local_58);
  if (local_30 == (FrameListener *)0x0) {
    local_34 = (WindowEventListener *)0x0;
  }
  else {
    local_34 = (WindowEventListener *)(local_30 + 4);
  }
  pWVar3 = local_34;
  iVar2 = FUN_0044d2a0();
  Ogre::WindowEventUtilities::addWindowEventListener(*(RenderWindow **)(iVar2 + 0xc),pWVar3);
  this = Ogre::Root::getSingletonPtr();
  Ogre::Root::addFrameListener(this,local_30);
  local_8 = 0xffffffff;
  FUN_006b3a50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

