
undefined4 FUN_0066f650(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ecb4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  switch(param_2) {
  case 0:
    pvVar2 = Ogre::StdAllocPolicy::allocateBytes(0x1c,(char *)0x0,0,(char *)0x0);
    iVar3 = forward<>(0x1c,pvVar2,uVar1);
    local_8 = 0;
    if (iVar3 == 0) {
      local_1c = 0;
      local_34 = local_1c;
    }
    else {
      local_34 = FUN_0066fcc0(param_1);
    }
    break;
  case 1:
    pvVar2 = Ogre::StdAllocPolicy::allocateBytes(0x1c,(char *)0x0,0,(char *)0x0);
    iVar3 = forward<>(0x1c,pvVar2,uVar1);
    local_8 = 1;
    if (iVar3 == 0) {
      local_24 = 0;
      local_34 = local_24;
    }
    else {
      local_34 = FUN_0066fd40(param_1);
    }
    break;
  case 2:
    pvVar2 = Ogre::StdAllocPolicy::allocateBytes(0x1c,(char *)0x0,0,(char *)0x0);
    iVar3 = forward<>(0x1c,pvVar2,uVar1);
    local_8 = 2;
    if (iVar3 == 0) {
      local_2c = 0;
      local_34 = local_2c;
    }
    else {
      local_34 = FUN_0066fdf0(param_1);
    }
    break;
  case 3:
    pvVar2 = Ogre::StdAllocPolicy::allocateBytes(0x18,(char *)0x0,0,(char *)0x0);
    iVar3 = forward<>(0x18,pvVar2,uVar1);
    local_8 = 3;
    if (iVar3 == 0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_0066f830();
    }
    break;
  default:
    local_34 = 0;
  }
  ExceptionList = local_10;
  return local_34;
}

