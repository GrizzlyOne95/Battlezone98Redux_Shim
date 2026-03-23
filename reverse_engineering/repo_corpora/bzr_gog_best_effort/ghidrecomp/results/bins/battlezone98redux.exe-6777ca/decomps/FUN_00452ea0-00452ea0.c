
void FUN_00452ea0(int param_1,undefined4 param_2)

{
  char cVar1;
  MaterialManager *this;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [8];
  float local_60;
  undefined4 local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_4c;
  int local_48;
  float local_44;
  int local_40;
  undefined4 local_3c;
  int local_34;
  undefined4 *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846bbe;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0044dec0(param_1,param_2);
  local_8 = 0;
  *local_30 = ShockRenderClass::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(local_30 + 0x51));
  local_8._0_1_ = 1;
  _vector_constructor_iterator_(local_30 + 0x53,0x10,2,_default_constructor_closure__exref);
  _vector_constructor_iterator_(local_30 + 0x5b,0x10,2,_default_constructor_closure__exref);
  if (param_1 == 0) {
    memset(local_30 + 0x41,0,0x40);
    local_30[0x53] = 0;
    local_30[0x54] = 0;
    local_30[0x55] = 0;
    local_30[0x56] = 0;
    local_30[0x57] = 0;
    local_30[0x58] = 0;
    local_30[0x59] = 0;
    local_30[0x5a] = 0;
    local_30[0x5b] = 0;
    local_30[0x5c] = 0;
    local_30[0x5d] = 0;
    local_30[0x5e] = 0;
    local_30[0x5f] = 0;
    local_30[0x60] = 0;
    local_30[0x61] = 0;
    local_30[0x62] = 0;
    local_30[99] = 0;
    local_30[100] = 0;
    local_30[0x65] = 0;
    local_30[0x66] = 0;
    local_30[0x67] = 0x7f7fffff;
    local_30[0x68] = 0x18;
    memset(local_30 + 0x69,0,0x800);
    memset(local_30 + 0x269,0,0x800);
    local_30[0x469] = 0;
  }
  else {
    FUN_00589430(local_30 + 0x25);
    local_8._0_1_ = 2;
    local_3c = FUN_00446460(local_30 + 0x15,0x811c9dc5);
    cVar1 = FUN_00449f30(local_3c,0xb311d4ef,local_30 + 0x41,param_1 + 0x104);
    if (cVar1 == '\0') {
      FUN_00449910(param_1 + 0x144);
    }
    else {
      basic_string<>(local_30 + 0x41);
      local_8._0_1_ = 3;
      pbVar7 = local_2c;
      pbVar6 = local_68;
      this = Ogre::MaterialManager::getSingleton();
      local_5c = Ogre::MaterialManager::getByName(this,pbVar6,pbVar7);
      local_8._0_1_ = 4;
      local_4c = local_5c;
      FUN_00449910(local_5c);
      local_8._0_1_ = 3;
      FUN_004499a0();
      local_8._0_1_ = 2;
      ~basic_string<>();
    }
    FUN_00589df0(local_3c,0xc14a56ec,local_30 + 0x53,*(undefined4 *)(param_1 + 0x14c),
                 *(undefined4 *)(param_1 + 0x150),*(undefined4 *)(param_1 + 0x154),
                 *(undefined4 *)(param_1 + 0x158));
    FUN_00589df0(local_3c,0xf928b815,local_30 + 0x5b,*(undefined4 *)(param_1 + 0x16c),
                 *(undefined4 *)(param_1 + 0x170),*(undefined4 *)(param_1 + 0x174),
                 *(undefined4 *)(param_1 + 0x178));
    FUN_00589df0(local_3c,&DAT_0151fdfd,local_30 + 0x57,*(undefined4 *)(param_1 + 0x15c),
                 *(undefined4 *)(param_1 + 0x160),*(undefined4 *)(param_1 + 0x164),
                 *(undefined4 *)(param_1 + 0x168));
    FUN_00589df0(local_3c,0x61bd8734,local_30 + 0x5f,*(undefined4 *)(param_1 + 0x17c),
                 *(undefined4 *)(param_1 + 0x180),*(undefined4 *)(param_1 + 0x184),
                 *(undefined4 *)(param_1 + 0x188));
    FUN_00589800(local_3c,0x335857b7,local_30 + 99,*(undefined4 *)(param_1 + 0x18c));
    FUN_00589800(local_3c,0xf1a39070,local_30 + 0x65,*(undefined4 *)(param_1 + 0x194));
    FUN_00589800(local_3c,0xf2397fc8,local_30 + 100,*(undefined4 *)(param_1 + 400));
    FUN_00589800(local_3c,0xa1f1020f,local_30 + 0x66,*(undefined4 *)(param_1 + 0x198));
    FUN_00589800(local_3c,0x54830e49,local_30 + 0x67,*(undefined4 *)(param_1 + 0x19c));
    FUN_005896c0(local_3c,0x615ad615,local_30 + 0x68,*(undefined4 *)(param_1 + 0x1a0));
    local_48 = 0x7f;
    for (local_40 = 0; local_40 <= local_48; local_40 = local_40 + 1) {
      local_44 = (float)local_40 / (float)local_48;
      for (local_34 = 0; local_34 < 2; local_34 = local_34 + 1) {
        local_58 = ((float)local_30[local_34 * 4 + 0x5b] - (float)local_30[local_34 * 4 + 0x53]) *
                   local_44 + (float)local_30[local_34 * 4 + 0x53];
        local_50 = ((float)local_30[local_34 * 4 + 0x5c] - (float)local_30[local_34 * 4 + 0x54]) *
                   local_44 + (float)local_30[local_34 * 4 + 0x54];
        local_54 = ((float)local_30[local_34 * 4 + 0x5d] - (float)local_30[local_34 * 4 + 0x55]) *
                   local_44 + (float)local_30[local_34 * 4 + 0x55];
        local_60 = ((float)local_30[local_34 * 4 + 0x5e] - (float)local_30[local_34 * 4 + 0x56]) *
                   local_44 + (float)local_30[local_34 * 4 + 0x56];
        iVar2 = FUN_008445c0();
        uVar3 = FUN_008445c0();
        uVar4 = FUN_008445c0();
        uVar5 = FUN_008445c0();
        local_30[local_40 * 2 + local_34 + 0x69] =
             iVar2 << 0x18 | (uVar3 & 0xff) << 0x10 | (uVar4 & 0xff) << 8 | uVar5 & 0xff;
        local_30[local_40 * 2 + local_34 + 0x269] =
             ((float)local_30[local_34 + 0x65] - (float)local_30[local_34 + 99]) * local_44 +
             (float)local_30[local_34 + 99];
      }
    }
    local_30[0x469] = (float)local_48 / (float)local_30[0x67];
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00589530();
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

