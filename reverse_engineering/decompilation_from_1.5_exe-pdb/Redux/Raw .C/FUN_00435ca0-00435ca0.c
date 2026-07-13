
void __fastcall FUN_00435ca0(int param_1)

{
  uint uStack_bc;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00845b2b;
  local_10 = ExceptionList;
  uStack_bc = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_bc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = uStack_bc;
  basic_string<>("RenderSystem_Direct3D9");
  local_8._0_1_ = 1;
  Ogre::Root::loadPlugin(*(Root **)(param_1 + 4),local_30);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  LoadLibraryA("D3DCompiler_43.dll");
  FUN_00435d41();
  return;
}

