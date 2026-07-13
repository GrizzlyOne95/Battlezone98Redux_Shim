
/* WARNING: Removing unreachable block (ram,0x007e296d) */

void __fastcall FUN_007e2900(undefined4 *param_1)

{
  undefined1 auStack_ac [128];
  undefined4 *puStack_2c;
  uint uStack_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined4 *local_1c;
  undefined *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00863b18;
  local_10 = ExceptionList;
  uStack_28 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_2c = param_1 + 2;
  local_20 = auStack_ac;
  local_1c = param_1;
  local_24 = FUN_007dd670(&stack0x00000004);
  local_11 = FUN_007e6b10();
  if (local_11 == '\0') {
    *local_1c = 0;
  }
  else {
    local_18 = &DAT_008a1bb8;
    *local_1c = &DAT_008a1bb8;
  }
  local_8 = 0xffffffff;
  puStack_2c = (undefined4 *)0x7e2998;
  FUN_007dba10();
  ExceptionList = local_10;
  return;
}

