
void FUN_007f93b0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_6c [31];
  undefined1 local_4d;
  undefined1 local_4c [56];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008640b8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar2 = FUN_007df2f0(local_14);
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_4);
    uVar3 = FUN_00423b10(uVar3);
    FUN_007384c0(uVar3);
    local_8 = 0;
    FUN_007f2400(local_4c,param_5,param_2);
    cVar1 = FUN_007df230(param_1,local_6c,param_3);
    if (cVar1 == '\0') {
      local_8 = 0xffffffff;
      FUN_0071b820();
    }
    else {
      operator==<>(param_1,*param_3);
      local_4d = 1;
      local_8 = 0xffffffff;
      FUN_0071b820();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

