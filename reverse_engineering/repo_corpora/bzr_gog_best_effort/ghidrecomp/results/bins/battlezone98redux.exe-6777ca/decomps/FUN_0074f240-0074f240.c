
undefined4
FUN_0074f240(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined1 auStack_38 [8];
  undefined4 uStack_30;
  undefined1 *puStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined1 local_20 [8];
  undefined1 local_18 [16];
  int *local_8;
  
  puStack_24 = local_18;
  uStack_28 = 0x74f255;
  FUN_0073a9b0();
  puStack_24 = local_18;
  uStack_28 = 0x74f261;
  FUN_006a9160();
  puStack_24 = (undefined1 *)0x74f266;
  local_8 = (int *)FUN_0074db30();
  puStack_24 = (undefined1 *)param_5;
  uStack_28 = param_4;
  puStack_2c = local_20;
  uStack_30 = param_3;
  FUN_0073a9b0(auStack_38);
  uVar1 = (**(code **)(*local_8 + 0x80))();
  return uVar1;
}

