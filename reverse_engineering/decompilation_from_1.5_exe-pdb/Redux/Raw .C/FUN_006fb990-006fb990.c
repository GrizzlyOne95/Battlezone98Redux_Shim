
undefined4 FUN_006fb990(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_ECX;
  undefined4 uVar1;
  undefined1 *puStack_2c;
  undefined4 *puStack_28;
  undefined1 *puStack_24;
  undefined1 local_1c [4];
  undefined1 local_18 [8];
  undefined4 local_10;
  undefined4 local_c [2];
  
  puStack_24 = (undefined1 *)0x6fb9a2;
  local_c[0] = FUN_006d4b30();
  puStack_24 = (undefined1 *)0x0;
  puStack_28 = (undefined4 *)param_4;
  uVar1 = extraout_ECX;
  FUN_006d1160(&param_3);
  FUN_006ee3f0(&puStack_2c,uVar1);
  FUN_0070bd90(local_1c,local_c,param_2);
  puStack_24 = (undefined1 *)0x6fb9df;
  local_10 = FUN_006d4b50();
  puStack_24 = local_18;
  puStack_28 = &local_10;
  puStack_2c = local_1c;
  puStack_28 = (undefined4 *)FUN_006d4b70();
  puStack_2c = (undefined1 *)0x6fb9ff;
  FUN_0070bea0();
  return param_1;
}

