
void __fastcall FUN_0072a490(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *puStack_1c;
  undefined4 *puStack_18;
  undefined4 *puStack_14;
  undefined4 local_10;
  undefined1 *local_c;
  undefined4 *local_8;
  
  puStack_14 = param_1 + 1;
  puStack_18 = (undefined4 *)0x72a4a5;
  local_8 = param_1;
  puStack_14 = (undefined4 *)FUN_00417780();
  puStack_18 = (undefined4 *)&stack0x00000004;
  puStack_1c = local_8 + 1;
  puStack_14 = (undefined4 *)FUN_00718e30(local_8);
  puStack_18 = local_8 + 1;
  puStack_1c = (undefined4 *)0x72a4cd;
  puStack_18 = (undefined4 *)FUN_00718e20();
  puStack_1c = (undefined4 *)&stack0x00000004;
  uVar1 = FUN_0070d630(local_8,local_8 + 1);
  local_c = (undefined1 *)&puStack_1c;
  local_10 = shared_ptr<>(uVar1);
  (*(code *)*local_8)();
  return;
}

