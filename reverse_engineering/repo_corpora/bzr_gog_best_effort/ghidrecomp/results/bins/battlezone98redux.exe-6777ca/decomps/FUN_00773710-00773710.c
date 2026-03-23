
void FUN_00773710(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined1 local_e4 [8];
  undefined1 local_dc [8];
  undefined1 local_d4 [8];
  undefined1 local_cc [184];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e1bb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007721c0(local_e4,1);
  uVar2 = FUN_00772230(uVar1);
  uVar2 = FUN_00417780(uVar2);
  FUN_004828f0(uVar2);
  local_8 = 0;
  uVar2 = _Val_type<>(param_1,param_2);
  uVar3 = FUN_00417780(local_cc,param_5,uVar2);
  puVar4 = (undefined4 *)FUN_007721c0(local_d4,1);
  uVar2 = puVar4[1];
  uVar5 = *puVar4;
  puVar4 = (undefined4 *)FUN_007721c0(local_dc,1);
  FUN_007738c0(param_1,param_2,*puVar4,puVar4[1],uVar5,uVar2,uVar3);
  local_8 = 0xffffffff;
  FUN_00482800();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

