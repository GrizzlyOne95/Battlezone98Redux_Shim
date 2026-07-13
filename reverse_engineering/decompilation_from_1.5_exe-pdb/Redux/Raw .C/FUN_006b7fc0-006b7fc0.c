
undefined4 FUN_006b7fc0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 auStack_cc [160];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [8];
  undefined1 *local_1c;
  uint local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850dfb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_18 = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  FUN_00422170(uVar2);
  puVar3 = (undefined4 *)FUN_00424640(local_24);
  local_14 = *puVar3;
  while( true ) {
    uVar4 = FID_conflict_begin(local_28);
    cVar1 = FUN_00420f10(uVar4);
    if (cVar1 == '\0') break;
    if (&stack0x00000000 == (undefined1 *)0xdc) {
      local_1c = (undefined1 *)0x0;
    }
    else {
      local_1c = auStack_cc;
    }
    iVar5 = FUN_00421ea0(&DAT_00871530);
    uVar4 = FUN_00421ea0(&DAT_00874924,iVar5 + 0x18);
    uVar4 = FUN_00574730(local_1c,uVar4);
    uVar4 = FUN_004bc590(uVar4);
    uVar4 = FUN_00574730(uVar4);
    FUN_004bc590(uVar4);
    FUN_004244c0(local_2c,0);
  }
  GetPolicy(param_1);
  local_18 = local_18 | 1;
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  return param_1;
}

