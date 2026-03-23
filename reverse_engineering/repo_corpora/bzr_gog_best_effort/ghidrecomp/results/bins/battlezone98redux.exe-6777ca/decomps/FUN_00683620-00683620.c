
void FUN_00683620(int param_1,int param_2)

{
  int iVar1;
  Root *pRVar2;
  RenderSystem *pRVar3;
  int iVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this;
  char *_Src;
  char *_Format;
  undefined1 *puVar5;
  char *local_6c;
  uint local_68;
  uint local_60;
  int local_50;
  char local_49;
  int local_48;
  undefined1 local_41;
  int local_40;
  char local_39;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((DAT_02cc3384 & 1) == 0) {
    DAT_02cc3384 = DAT_02cc3384 | 1;
    basic_string<>(&DAT_00873de0);
    FUN_0083e979(FUN_00867890);
  }
  if ((DAT_02cc3384 & 2) == 0) {
    DAT_02cc3384 = DAT_02cc3384 | 2;
    basic_string<>(&DAT_00873e10);
    FUN_0083e979(FUN_00867880);
  }
  iVar1 = FUN_00685520();
  if (iVar1 != 0) {
    FUN_006854f0();
  }
  FUN_00685410();
  basic_string<>("Full Screen");
  pRVar2 = Ogre::Root::getSingleton();
  pRVar3 = Ogre::Root::getRenderSystem(pRVar2);
  puVar5 = local_38;
  (**(code **)(*(int *)pRVar3 + 0xc))(puVar5);
  iVar4 = FUN_004b2f10(puVar5);
  this = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
         (iVar4 + 0x18);
  ~basic_string<>();
  basic_string<>("Video Mode");
  pRVar2 = Ogre::Root::getSingleton();
  pRVar3 = Ogre::Root::getRenderSystem(pRVar2);
  puVar5 = local_20;
  (**(code **)(*(int *)pRVar3 + 0xc))(puVar5);
  iVar4 = FUN_004b2f10(puVar5);
  ~basic_string<>(this,iVar4 + 0x18);
  _Format = "%d x %d";
  _Src = (char *)FUN_0041f870("%d x %d",&local_48,&local_50);
  sscanf(_Src,_Format);
  iVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::compare
                    (this,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)&DAT_02cc3348);
  local_39 = iVar4 != 0;
  local_49 = DAT_009183b8 != 0;
  local_40 = FUN_0044d2a0();
  FUN_00435ef0(0);
  if (local_49 != '\0') {
    ShowWindow(DAT_02cf44a0,6);
    ShowWindow(DAT_02cf44a0,9);
  }
  if (((local_39 != '\0') && (DAT_009183b8 != 0)) && (param_1 != 0)) {
    FUN_004363a0(&local_48,&local_50);
    (**(code **)(**(int **)(local_40 + 0xc) + 0x10c))(0,local_48 + -1,local_50 + -1);
    local_60 = (uint)(local_39 != '\0');
    DAT_009183b8 = local_60;
  }
  if (param_1 != 0) {
    if (local_39 == '\0') {
      (**(code **)(**(int **)(local_40 + 0xc) + 0x10c))(0,local_48 + 1,local_50 + 1);
      FUN_00435ef0(0);
      (**(code **)(**(int **)(local_40 + 0xc) + 0x10c))(0,local_48,local_50);
    }
    else {
      FUN_004363a0(&local_48,&local_50);
      (**(code **)(**(int **)(local_40 + 0xc) + 0x10c))(1,local_48,local_50);
    }
  }
  local_68 = (uint)(local_39 != '\0');
  DAT_009183b8 = local_68;
  local_41 = param_2 != 0;
  FUN_00435ef0(local_41);
  FUN_00435bc0();
  FUN_007c6920();
  FUN_00681df0();
  if (DAT_00918320 != 0) {
    FUN_007c6760();
  }
  if (DAT_00918320 != 0) {
    FUN_005d4260();
  }
  if (local_39 == '\0') {
    local_6c = "windowed";
  }
  else {
    local_6c = "full screen";
  }
  FUN_007d6a70("Created %s window sized (%d,%d)\n",local_6c,local_48,local_50);
  if (param_1 != 0) {
    pRVar2 = Ogre::Root::getSingleton();
    Ogre::Root::saveConfig(pRVar2);
  }
  if (iVar1 != 0) {
    FUN_006854d0();
  }
  FUN_0083e885();
  return;
}

