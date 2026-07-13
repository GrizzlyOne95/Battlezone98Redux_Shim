
int FUN_004775b0(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  int local_28;
  int local_24;
  int local_20;
  void *local_1c;
  int local_18;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084733c;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0042d8c0(local_14);
  while( true ) {
    uVar3 = FID_conflict_begin(local_30);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      local_1c = operator_new(0x10);
      local_8 = 0;
      if (local_1c == (void *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = FUN_004776c0();
      }
      local_28 = local_20;
      local_8 = 0xffffffff;
      local_18 = local_20;
      uVar3 = FUN_00477590(param_1);
      *(undefined4 *)(local_18 + 4) = uVar3;
      FUN_00438be0(&local_18);
      ExceptionList = local_10;
      return local_18;
    }
    piVar4 = (int *)FUN_0042de50(uVar2);
    local_24 = FUN_00462630(*(undefined4 *)(*piVar4 + 4));
    if (local_24 == param_1) break;
    FUN_00438c10(local_2c,0);
  }
  piVar4 = (int *)FUN_0042de50();
  ExceptionList = local_10;
  return *piVar4;
}

