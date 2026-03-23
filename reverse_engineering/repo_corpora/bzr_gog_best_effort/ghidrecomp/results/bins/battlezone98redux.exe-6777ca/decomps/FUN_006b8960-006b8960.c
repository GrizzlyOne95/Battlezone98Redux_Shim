
void FUN_006b8960(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  code *pcVar6;
  undefined1 local_d8 [4];
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  undefined1 local_cc [4];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined1 local_b4 [136];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850f38;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  uVar3 = FUN_004fee40(local_d8);
  pcVar6 = FUN_006b6820;
  puVar4 = (undefined4 *)FUN_004fee40(local_cc);
  uVar5 = *puVar4;
  puVar4 = (undefined4 *)FID_conflict_begin(local_d4);
  FUN_006d9b70(local_d0,*puVar4,uVar5,pcVar6,uVar3,uVar2);
  cVar1 = FID_conflict_operator__(uVar3);
  if (cVar1 != '\0') {
    basic_string<>("Invalid method token.");
    local_8 = 0;
    local_c4 = basic_string<>();
    local_8._0_1_ = 1;
    local_bc = local_c4;
    local_c8 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    local_c0 = local_c8;
    FUN_006b7140(local_2c,400,local_c8,local_bc);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_b4,(ThrowInfo *)&DAT_008d838c);
  }
  FID_conflict_operator_(param_1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

