
void FUN_007734f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined1 local_e0 [8];
  undefined1 local_d8 [8];
  undefined1 local_d0 [8];
  undefined1 local_c8 [180];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e17b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_007721c0(local_e0,1);
  uVar2 = FUN_00772160(uVar1);
  uVar2 = FUN_00417780(uVar2);
  FUN_00753550(uVar2);
  local_8 = 0;
  uVar2 = _Val_type<>(param_1,param_2);
  uVar3 = FUN_00417780(local_c8,param_5,uVar2);
  puVar4 = (undefined4 *)FUN_007721c0(local_d0,1);
  uVar2 = puVar4[1];
  uVar5 = *puVar4;
  puVar4 = (undefined4 *)FUN_007721c0(local_d8,1);
  FUN_00773860(param_1,param_2,*puVar4,puVar4[1],uVar5,uVar2,uVar3);
  local_8 = 0xffffffff;
  FUN_00753670();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

