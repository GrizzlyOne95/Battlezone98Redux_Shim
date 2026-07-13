
void __thiscall
FUN_006687b0(int *param_1,undefined4 param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3,
            char param_4)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  void *pvVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  basic_ifstream<char,struct_std::char_traits<char>_> *local_120;
  FileStreamDataStream *local_11c;
  basic_ifstream<char,struct_std::char_traits<char>_> *local_118;
  FileStreamDataStream *local_114;
  FileStreamDataStream *local_10c;
  basic_ifstream<char,struct_std::char_traits<char>_> *local_100;
  basic_ifstream<char,struct_std::char_traits<char>_> *local_f4;
  basic_fstream<char,struct_std::char_traits<char>_> *local_f0;
  undefined1 local_ec [20];
  uint local_d8;
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e627;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  iVar4 = FUN_00669800(param_3);
  basic_string<>(uVar3);
  local_8 = 0;
  if (iVar4 == 0) {
    uVar5 = FUN_006678e0(local_a4,param_1 + 1,param_3);
    FUN_0045e0f0(uVar5);
    ~basic_string<>();
  }
  else {
    uVar5 = FUN_006678e0(local_bc,param_1 + 0x11,iVar4 + 4);
    FUN_0045e0f0(uVar5);
    ~basic_string<>();
  }
  uVar5 = FUN_0041f870(local_ec);
  uVar5 = FUN_00666ce0(uVar5);
  local_f4 = (basic_ifstream<char,struct_std::char_traits<char>_> *)0x0;
  local_f0 = (basic_fstream<char,struct_std::char_traits<char>_> *)0x0;
  if (param_4 == '\0') {
    cVar1 = (**(code **)(*param_1 + 0x10))(uVar3,uVar5);
    if (cVar1 != '\0') {
      basic_string<>("FileSystemArchive::open");
      local_8._0_1_ = 1;
      basic_string<>("Cannot open a file in read-write mode in a read-only archive");
      local_8._0_1_ = 2;
      FUN_00666d00(2,2,local_44,local_74,"OgreRender\\Ogre76Archive.cpp",0xfa);
      local_8._0_1_ = 1;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
  }
  if (param_4 == '\0') {
    uVar5 = 0x23;
    pvVar6 = Ogre::StdAllocPolicy::allocateBytes(0xc0,(char *)0x0,0,(char *)0x0);
    iVar4 = forward<>(0xc0,pvVar6);
    local_8._0_1_ = 3;
    if (iVar4 == 0) {
      local_118 = (basic_ifstream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_118 = (basic_ifstream<char,struct_std::char_traits<char>_> *)FUN_0066af10(1);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    local_f0 = (basic_fstream<char,struct_std::char_traits<char>_> *)local_118;
    uVar8 = 0x40;
    uVar7 = FUN_0041f870(0x23,0x40);
    FUN_0066b050(uVar7,uVar5,uVar8);
    local_100 = local_118;
  }
  else {
    pvVar6 = Ogre::StdAllocPolicy::allocateBytes(0xb8,(char *)0x0,0,(char *)0x0);
    iVar4 = forward<>(0xb8,pvVar6);
    local_8._0_1_ = 4;
    if (iVar4 == 0) {
      local_120 = (basic_ifstream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_120 = (basic_ifstream<char,struct_std::char_traits<char>_> *)FUN_00421fc0(1);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    local_f4 = local_120;
    uVar8 = 0x40;
    uVar7 = 0x21;
    uVar5 = FUN_0041f870(0x21,0x40);
    FUN_004220f0(uVar5,uVar7,uVar8);
    local_100 = local_120;
  }
  bVar2 = std::ios_base::fail((ios_base *)(local_100 + *(int *)(*(int *)local_100 + 4)));
  if (bVar2) {
    if (local_f4 != (basic_ifstream<char,struct_std::char_traits<char>_> *)0x0) {
      (*(code *)**(undefined4 **)(local_f4 + *(int *)(*(int *)local_f4 + 4)))(0);
      Ogre::StdAllocPolicy::deallocateBytes(local_f4);
    }
    if (local_f0 != (basic_fstream<char,struct_std::char_traits<char>_> *)0x0) {
      (*(code *)**(undefined4 **)(local_f0 + *(int *)(*(int *)local_f0 + 4)))(0);
      Ogre::StdAllocPolicy::deallocateBytes(local_f0);
    }
    basic_string<>("FileSystemArchive::open");
    local_8._0_1_ = 5;
    uVar5 = FUN_0066e860(local_8c,"Cannot open file: ",param_3);
    local_8._0_1_ = 6;
    FUN_00666d00(6,6,uVar5,local_5c,"OgreRender\\Ogre76Archive.cpp",0x113);
    local_8._0_1_ = 5;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  if (local_f0 == (basic_fstream<char,struct_std::char_traits<char>_> *)0x0) {
    local_11c = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x34);
    local_8._0_1_ = 8;
    if (local_11c == (FileStreamDataStream *)0x0) {
      local_11c = (FileStreamDataStream *)0x0;
    }
    else {
      Ogre::FileStreamDataStream::FileStreamDataStream(local_11c,param_3,local_f4,local_d8,true);
      *(undefined ***)local_11c = Ogre::FileStreamDataStream::vftable;
    }
    local_10c = local_11c;
  }
  else {
    local_114 = Ogre::AllocatedObject<class_Ogre::CategorisedAllocPolicy<0>_>::operator_new(0x34);
    local_8._0_1_ = 7;
    if (local_114 == (FileStreamDataStream *)0x0) {
      local_114 = (FileStreamDataStream *)0x0;
    }
    else {
      Ogre::FileStreamDataStream::FileStreamDataStream(local_114,param_3,local_f0,local_d8,true);
      *(undefined ***)local_114 = Ogre::FileStreamDataStream::vftable;
    }
    local_10c = local_114;
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0066e920(local_10c,0);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

