
void __fastcall FUN_006630c0(undefined4 *param_1)

{
  uint uVar1;
  MaterialManager *pMVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0084dc2b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = MatListener::vftable;
  local_8 = 1;
  local_14 = uVar1;
  basic_string<>(&DAT_00892124);
  local_8._0_1_ = 2;
  pMVar2 = Ogre::MaterialManager::getSingleton();
  (**(code **)(*(int *)pMVar2 + 0xb0))(param_1,local_2c,uVar1);
  local_8._0_1_ = 1;
  ~basic_string<>();
  FUN_004c85d0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_00662e50();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

