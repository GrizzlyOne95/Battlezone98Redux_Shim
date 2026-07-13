
void FUN_00806230(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_2c;
  undefined4 local_28;
  int *local_24;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00806540(&local_28,param_1,param_3,&local_2c);
  *(undefined4 *)(*local_24 + 0x18) = local_2c;
  uVar2 = FUN_00806670(local_20,local_28,param_2);
  FUN_0045e0f0(uVar2);
  ~basic_string<>();
  uVar2 = FUN_00806620(local_28,param_3);
  *(undefined4 *)(*local_24 + 0x1c) = uVar2;
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 == '\0') {
    FUN_007d6fc0(1);
  }
  else {
    FUN_007d6fc0(2);
  }
  FUN_0083e885();
  return;
}

