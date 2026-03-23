
undefined4 * __thiscall FUN_006616a0(undefined4 *param_1,Entity *param_2)

{
  uint uVar1;
  SubEntity *pSVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  void *local_1c;
  undefined4 *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d9c7;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = EntityTransparency::vftable;
  local_18 = param_1;
  vector<>(uVar1);
  local_8 = 0;
  if (param_2 != (Entity *)0x0) {
    local_14 = 0;
    while (uVar1 = Ogre::Entity::getNumSubEntities(param_2), local_14 < uVar1) {
      local_1c = operator_new(0x20);
      local_8._0_1_ = 1;
      if (local_1c == (void *)0x0) {
        local_20 = 0;
      }
      else {
        pSVar2 = Ogre::Entity::getSubEntity(param_2,local_14);
        local_20 = FUN_00662210(pSVar2);
      }
      local_24 = local_20;
      local_8 = (uint)local_8._1_3_ << 8;
      local_28 = local_20;
      FUN_0041ff90(&local_28);
      local_14 = local_14 + 1;
    }
  }
  ExceptionList = local_10;
  return local_18;
}

