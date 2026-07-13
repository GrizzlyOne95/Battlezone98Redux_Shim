
void FUN_0067e130(void)

{
  uint uVar1;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f068;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("terrain_masterlight");
  local_8 = 0;
  (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x13c))(local_2c,uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  DAT_00920ca0 = 0;
  DAT_0091815b = 0;
  CPngImage::CleanUp();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

