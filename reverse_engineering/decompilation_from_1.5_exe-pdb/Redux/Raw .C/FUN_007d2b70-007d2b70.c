
void __fastcall FUN_007d2b70(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00862bb0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  if (*(int *)(param_1 + 0x120) == 0) {
    basic_string<>(param_1 + 0x20);
    local_8._0_1_ = 1;
    iVar1 = FUN_0044d2a0();
    uVar2 = (**(code **)(**(int **)(iVar1 + 8) + 0x1a0))(local_2c);
    *(undefined4 *)(param_1 + 0x120) = uVar2;
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    uVar3 = FUN_007d3ee0();
    (**(code **)(**(int **)(param_1 + 0x120) + 0xa8))((uVar3 & 0xff) + 0x3c);
    uVar2 = (**(code **)(**(int **)(DAT_00920ea0 + 8) + 0x164))();
    *(undefined4 *)(param_1 + 0x11c) = uVar2;
    (**(code **)(**(int **)(param_1 + 0x11c) + 0x124))(*(undefined4 *)(param_1 + 0x120));
    Ogre::ManualObject::setUseIdentityView(*(ManualObject **)(param_1 + 0x120),true);
    Ogre::ManualObject::setUseIdentityProjection(*(ManualObject **)(param_1 + 0x120),true);
    piVar4 = (int *)get();
    uVar2 = (**(code **)(*piVar4 + 0x58))(4,DEFAULT_RESOURCE_GROUP_NAME_exref);
    (**(code **)(**(int **)(param_1 + 0x120) + 0x10c))(uVar2);
    FUN_007d2e20();
    (**(code **)(**(int **)(param_1 + 0x120) + 0x16c))();
  }
  else {
    piVar4 = (int *)get(local_14);
    uVar2 = (**(code **)(*piVar4 + 0x58))(DEFAULT_RESOURCE_GROUP_NAME_exref);
    (**(code **)(**(int **)(param_1 + 0x120) + 0x170))(0,uVar2);
    (**(code **)(**(int **)(param_1 + 0x120) + 0x84))(1);
  }
  FUN_00449910(&stack0x00000004);
  local_8 = 0xffffffff;
  FUN_004499a0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

