
undefined4 * __thiscall FUN_0044bca0(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846590;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0044dec0(param_2,param_3);
  local_8 = 0;
  *param_1 = EmitRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x41] = 0;
    param_1[0x42] = 0x7f7fffff;
    param_1[0x43] = 0;
    param_1[0x44] = 0;
    param_1[0x45] = 0;
    param_1[0x46] = 0;
    param_1[0x47] = 0;
    param_1[0x48] = 0;
    param_1[0x49] = 0;
    param_1[0x4a] = 0;
    param_1[0x4b] = 0;
    param_1[0x4c] = 0;
  }
  else {
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00589430(param_1 + 0x25);
    local_8._0_1_ = 1;
    FUN_0058a050(uVar2,0x74d29c11,param_1 + 0x41,*(undefined4 *)(param_2 + 0x104));
    FUN_00589800(uVar2,0x73965b8d,param_1 + 0x42,*(undefined4 *)(param_2 + 0x108));
    FUN_00589800(uVar2,0xf92c3036,param_1 + 0x43,*(undefined4 *)(param_2 + 0x10c));
    FUN_00589ca0(uVar2,0x2cb72e51,param_1 + 0x44,*(undefined4 *)(param_2 + 0x110),
                 *(undefined4 *)(param_2 + 0x114),*(undefined4 *)(param_2 + 0x118));
    FUN_00589ca0(uVar2,0xf45716fd,param_1 + 0x47,*(undefined4 *)(param_2 + 0x11c),
                 *(undefined4 *)(param_2 + 0x120),*(undefined4 *)(param_2 + 0x124));
    FUN_00589ca0(uVar2,0x55d04c01,param_1 + 0x4a,*(undefined4 *)(param_2 + 0x128),
                 *(undefined4 *)(param_2 + 300),*(undefined4 *)(param_2 + 0x130));
    param_1[0x4d] = (float)param_1[0x42] * 4.0;
    param_1[0x4e] = (float)param_1[0x42] * 2.0;
    param_1[0x4f] = (float)param_1[0x42] * 1.0;
    param_1[0x50] = (float)param_1[0x43] * 4.0;
    param_1[0x51] = (float)param_1[0x43] * 2.0;
    param_1[0x52] = (float)param_1[0x43] * 1.0;
    FUN_0044c760(2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return param_1;
}

