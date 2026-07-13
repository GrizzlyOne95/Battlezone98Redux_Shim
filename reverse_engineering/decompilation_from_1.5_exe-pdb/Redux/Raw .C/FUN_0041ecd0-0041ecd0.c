
int FUN_0041ecd0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_2c [12];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845058;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0041d750(local_1c);
  local_14 = 3;
  uVar3 = FID_conflict_begin(local_20);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_00421ea0(uVar2);
    FUN_0041fac0(iVar4 + 0x18);
    local_8 = 0;
    local_14 = FUN_0041eba0(param_1,local_2c);
    local_8 = 0xffffffff;
    FUN_0041fbb0();
  }
  if (local_14 == 3) {
    local_14 = FUN_0041eba0(param_1,local_18 + 0xac);
  }
  ExceptionList = local_10;
  return local_14;
}

