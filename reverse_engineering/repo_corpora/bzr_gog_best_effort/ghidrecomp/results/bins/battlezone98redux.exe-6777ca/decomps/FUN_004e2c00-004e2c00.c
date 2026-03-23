
void __fastcall FUN_004e2c00(undefined4 *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 **ppuVar4;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084a306;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Geizer::vftable;
  param_1[6] = Geizer::vftable;
  local_8 = 1;
  local_14 = param_1;
  FUN_004e2d90(uVar1);
  local_18 = local_14;
  puVar2 = (undefined4 *)FID_conflict_end(local_24);
  local_1c = *puVar2;
  ppuVar4 = &local_18;
  puVar2 = (undefined4 *)FID_conflict_end(local_28);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_2c);
  puVar2 = (undefined4 *)FUN_0046e930(local_30,*puVar2,uVar3,ppuVar4);
  local_20 = *puVar2;
  FID_conflict_erase(local_34,local_20,local_1c);
  local_8 = local_8 & 0xffffff00;
  FUN_0044dc30();
  local_8 = 0xffffffff;
  FUN_0047eab0();
  ExceptionList = local_10;
  return;
}

