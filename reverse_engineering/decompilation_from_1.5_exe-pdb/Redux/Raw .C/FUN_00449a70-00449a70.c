
void __fastcall FUN_00449a70(int *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008462e0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*param_1 == 0) {
    uVar3 = FUN_00448980(1,"boost unique_lock has no mutex");
    local_8 = 0;
    FUN_00449e90(uVar3);
    local_8 = 0xffffffff;
    FUN_004489b0();
  }
  cVar1 = FUN_0041f990(uVar2);
  if (cVar1 != '\0') {
    uVar3 = FUN_00448980(0x24,"boost unique_lock owns already the mutex");
    local_8 = 1;
    FUN_00449e90(uVar3);
    local_8 = 0xffffffff;
    FUN_004489b0();
  }
  FUN_00449c90();
  *(undefined1 *)(param_1 + 1) = 1;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

