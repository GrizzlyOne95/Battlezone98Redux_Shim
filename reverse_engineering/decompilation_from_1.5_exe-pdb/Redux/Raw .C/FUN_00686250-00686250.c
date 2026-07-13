
void FUN_00686250(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_34 [8];
  int *local_2c;
  undefined4 local_28;
  int *local_24;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = Ogre::ManualObject::getNumSections((ManualObject *)DAT_00920edc);
  if (uVar1 != 0) {
    basic_string<>(&DAT_0088b2d8);
    uVar2 = (**(code **)(*DAT_00920edc + 0x174))
                      (local_34,local_20,DEFAULT_RESOURCE_GROUP_NAME_exref);
    FUN_00449910(uVar2);
    FUN_004499a0();
    ~basic_string<>();
    DAT_00920ee8 = FUN_00685e00(&DAT_025f8f04,1);
    DAT_00920ef0 = FUN_00685e00(&DAT_025f8f04,2);
    DAT_00920eec = FUN_00685e00(&DAT_025f8f04,4);
    DAT_00920ee0 = FUN_00685cb0("SkyMain",DAT_00920ee8);
    DAT_00920ee4 = FUN_00685cb0("SkyTarget",DAT_00920ef0);
    DAT_00920ed8 = FUN_00685cb0("SkySniper",DAT_00920eec);
  }
  (**(code **)(*DAT_00920edc + 0x100))();
  local_2c = DAT_00920edc;
  local_24 = DAT_00920edc;
  if (DAT_00920edc == (int *)0x0) {
    local_28 = 0;
  }
  else {
    local_28 = (**(code **)*DAT_00920edc)(1);
  }
  DAT_00920edc = (int *)0x0;
  FUN_0083e885();
  return;
}

