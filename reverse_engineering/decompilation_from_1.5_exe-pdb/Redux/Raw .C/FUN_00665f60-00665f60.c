
void __thiscall FUN_00665f60(int param_1,undefined1 *param_2,uint *param_3,uint *param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_e4 [4];
  undefined1 local_e0 [4];
  undefined1 local_dc [4];
  undefined1 local_d8 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_d4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_d0;
  undefined4 local_cc;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_c8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_c4;
  undefined4 local_c0;
  int local_bc;
  RenderSystem *local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  int local_ac;
  undefined1 local_a6;
  undefined1 local_a5;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e1ab;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_bc = param_1;
  local_14 = uVar2;
  if ((*(int *)(param_1 + 4) == 0) ||
     (local_b8 = Ogre::Root::getRenderSystem(*(Root **)(param_1 + 4)),
     local_b8 == (RenderSystem *)0x0)) goto LAB_0066627d;
  local_b4 = (**(code **)(*(int *)local_b8 + 0xc))(uVar2);
  FUN_00422170();
  basic_string<>("Video Mode");
  local_8 = 0;
  puVar3 = (undefined4 *)FUN_00421e00(local_dc,local_5c);
  local_b0 = *puVar3;
  local_8 = 0xffffffff;
  ~basic_string<>();
  uVar4 = FID_conflict_begin(local_e4);
  cVar1 = FUN_004221b0(uVar4);
  if (cVar1 != '\0') goto LAB_0066627d;
  iVar5 = FUN_00421ea0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)(iVar5 + 0x30));
  local_8 = 1;
  local_ac = FUN_005871b0(&DAT_008921ec,0);
  if (local_ac != -1) {
    local_cc = FUN_0045e1d0(local_a4,0,local_ac);
    FUN_0045e0f0(local_cc);
    ~basic_string<>();
  }
  local_ac = FUN_00666640(0x78,0);
  if (local_ac == -1) {
    local_a5 = 0;
    local_8 = 0xffffffff;
    ~basic_string<>();
    goto LAB_0066627d;
  }
  local_d4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_0045e1d0(local_74,0,local_ac);
  local_8._0_1_ = 2;
  local_c8 = local_d4;
  uVar2 = Ogre::StringConverter::parseUnsignedInt(local_d4,0);
  *param_3 = uVar2;
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_d0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_0045e1d0(local_8c,local_ac + 1,0xffffffff);
  local_8._0_1_ = 3;
  local_c4 = local_d0;
  uVar2 = Ogre::StringConverter::parseUnsignedInt(local_d0,0);
  *param_4 = uVar2;
  local_8._0_1_ = 1;
  ~basic_string<>();
  basic_string<>("Full Screen");
  local_8._0_1_ = 4;
  puVar3 = (undefined4 *)FUN_00421e00(local_e0,local_44);
  local_b0 = *puVar3;
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  uVar4 = FID_conflict_begin(local_d8);
  cVar1 = FUN_004221b0(uVar4);
  if (cVar1 == '\0') {
    iVar5 = FUN_00421ea0(&DAT_00873e10);
    cVar1 = FUN_00427270(iVar5 + 0x30);
    if (cVar1 != '\0') goto LAB_0066624c;
    local_c0 = 0;
  }
  else {
LAB_0066624c:
    local_c0 = 1;
  }
  *param_2 = (undefined1)local_c0;
  local_a6 = 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_0066627d:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

