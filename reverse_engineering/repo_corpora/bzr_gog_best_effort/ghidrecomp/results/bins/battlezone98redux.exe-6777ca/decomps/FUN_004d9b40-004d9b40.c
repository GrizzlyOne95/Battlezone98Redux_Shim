
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004d9b40(void)

{
  int iVar1;
  int iVar2;
  MaterialManager *pMVar3;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a048;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = FUN_00417c70(local_14);
  iVar2 = FUN_004344a0();
  if (iVar1 != 0) {
    if (iVar2 == 2) {
      DAT_02cc2f3c = 'H';
      DAT_02cc2f3c_1._0_1_ = 'U';
      DAT_02cc2f3c_1._1_1_ = 'D';
      DAT_02cc2f3c_1._2_1_ = 'I';
      DAT_02cc2f40 = 'P';
      DAT_02cc2f40_1._0_1_ = 'a';
      DAT_02cc2f40_1._1_1_ = 'd';
      DAT_02cc2f43 = 'i';
    }
    else {
      DAT_02cc2f3c = 'H';
      DAT_02cc2f3c_1._0_1_ = 'U';
      DAT_02cc2f3c_1._1_1_ = 'D';
      DAT_02cc2f3c_1._2_1_ = 'c';
      DAT_02cc2f40 = 'o';
      DAT_02cc2f40_1._0_1_ = 'm';
      DAT_02cc2f40_1._1_1_ = 'b';
      DAT_02cc2f43 = 'a';
    }
    DAT_02cc2f44 = 0;
    iVar1 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
    _DAT_02cc2f40 = CONCAT13(*(undefined1 *)(iVar1 + 0xcc),_DAT_02cc2f40);
    basic_string<>(&DAT_02cc2f3c);
    local_8 = 0;
    pMVar3 = Ogre::MaterialManager::getSingleton();
    (**(code **)(*(int *)pMVar3 + 0x54))(local_2c);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

