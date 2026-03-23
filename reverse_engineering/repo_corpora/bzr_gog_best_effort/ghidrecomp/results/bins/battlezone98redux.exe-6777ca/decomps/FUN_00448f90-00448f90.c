
void FUN_00448f90(int param_1,undefined4 param_2)

{
  char cVar1;
  MaterialManager *this;
  undefined4 *puVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  ColourValue local_6c [16];
  ColourValue local_5c [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_4c [8];
  undefined4 local_44;
  undefined4 local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008461de;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0044dec0(param_1,param_2);
  local_8 = 0;
  *local_30 = ColorRenderClass::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(local_30 + 0x51));
  local_8._0_1_ = 1;
  Ogre::ColourValue::ColourValue((ColourValue *)(local_30 + 0x53),1.0,1.0,1.0,1.0);
  Ogre::ColourValue::ColourValue((ColourValue *)(local_30 + 0x57),1.0,1.0,1.0,1.0);
  if (param_1 == 0) {
    memset(local_30 + 0x41,0,0x40);
    puVar2 = (undefined4 *)Ogre::ColourValue::ColourValue(local_5c,0.0,0.0,0.0,0.0);
    local_30[0x53] = *puVar2;
    local_30[0x54] = puVar2[1];
    local_30[0x55] = puVar2[2];
    local_30[0x56] = puVar2[3];
    puVar2 = (undefined4 *)Ogre::ColourValue::ColourValue(local_6c,0.0,0.0,0.0,0.0);
    local_30[0x57] = *puVar2;
    local_30[0x58] = puVar2[1];
    local_30[0x59] = puVar2[2];
    local_30[0x5a] = puVar2[3];
    local_30[0x5b] = 0;
    local_30[0x5c] = 0;
    local_30[0x5d] = 0x7f7fffff;
    local_30[0x5e] = 0;
  }
  else {
    FUN_00589430(local_30 + 0x25);
    local_8._0_1_ = 2;
    local_38 = FUN_00446460(local_30 + 0x15,0x811c9dc5);
    cVar1 = FUN_00449f30(local_38,0xb311d4ef,local_30 + 0x41,param_1 + 0x104);
    if (cVar1 == '\0') {
      FUN_00449910(param_1 + 0x144);
    }
    else {
      basic_string<>(local_30 + 0x41);
      local_8._0_1_ = 3;
      pbVar4 = local_2c;
      pbVar3 = local_4c;
      this = Ogre::MaterialManager::getSingleton();
      local_44 = Ogre::MaterialManager::getByName(this,pbVar3,pbVar4);
      local_8._0_1_ = 4;
      local_40 = local_44;
      FUN_00449910(local_44);
      local_8._0_1_ = 3;
      FUN_004499a0();
      local_8._0_1_ = 2;
      ~basic_string<>();
    }
    FUN_00589df0(local_38,0x3f9a5cee,local_30 + 0x53,*(undefined4 *)(param_1 + 0x14c),
                 *(undefined4 *)(param_1 + 0x150),*(undefined4 *)(param_1 + 0x154),
                 *(undefined4 *)(param_1 + 0x158));
    FUN_00589df0(local_38,0x58ba3165,local_30 + 0x57,*(undefined4 *)(param_1 + 0x15c),
                 *(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x164),
                 *(undefined4 *)(param_1 + 0x168));
    FUN_00589800(local_38,0x69a1e45d,local_30 + 0x5b,*(undefined4 *)(param_1 + 0x16c));
    FUN_00589800(local_38,&DAT_00a73260,local_30 + 0x5c,*(undefined4 *)(param_1 + 0x170));
    FUN_00589800(local_38,0x54830e49,local_30 + 0x5d,*(undefined4 *)(param_1 + 0x174));
    if ((float)local_30[0x5d] <= 0.0) {
      local_3c = 0.0;
    }
    else {
      local_3c = 1.0 / (float)local_30[0x5d];
    }
    local_30[0x5e] = local_3c;
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00589530();
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

