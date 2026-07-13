
undefined4 __thiscall FUN_007bbca0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861874;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pvVar3 = operator_new(0x14);
  local_8 = 0;
  if (pvVar3 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_007bb7f0(uVar2);
  }
  local_8 = 0xffffffff;
  FUN_007bd720(local_20);
  local_8 = 1;
  iVar4 = get();
  *(undefined4 *)(iVar4 + 0x10) = 0;
  uVar5 = FUN_007bb700(param_2);
  local_8._0_1_ = 2;
  get(uVar5);
  FUN_007bd000(uVar5);
  local_8._0_1_ = 1;
  FUN_00667660();
  uVar5 = FUN_00667590();
  local_8._0_1_ = 3;
  get(uVar5);
  uVar5 = FUN_007bd050();
  cVar1 = FUN_007bd6f0(uVar5);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00667660();
  if (cVar1 != '\0') {
    FUN_006c8b90();
  }
  ExceptionList = local_10;
  return param_1;
}

