
void FUN_006b7570(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  code *pcVar6;
  undefined1 local_f8 [4];
  undefined1 local_f4 [4];
  undefined1 local_f0 [4];
  undefined1 local_ec [4];
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined1 local_cc [136];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850c90;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  uVar3 = FUN_004fee40(local_ec);
  pcVar6 = FUN_006b6820;
  puVar4 = (undefined4 *)FUN_004fee40(local_f0);
  uVar5 = *puVar4;
  puVar4 = (undefined4 *)FID_conflict_begin(local_f8);
  FUN_006d9b70(local_f4,*puVar4,uVar5,pcVar6,uVar3,uVar2);
  cVar1 = FID_conflict_operator__(uVar3);
  if (cVar1 != '\0') {
    basic_string<>("Invalid header name");
    local_8 = 0;
    local_e4 = basic_string<>();
    local_8._0_1_ = 1;
    local_e0 = local_e4;
    local_dc = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    local_d8 = local_dc;
    FUN_006b7140(local_2c,400,local_dc,local_e4);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_cc,(ThrowInfo *)&DAT_008d838c);
  }
  FUN_006b7490(param_1);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    uVar5 = FUN_0066e860(local_44,&DAT_00892870,param_2);
    local_8 = 3;
    local_e8 = uVar5;
    local_d4 = uVar5;
    FUN_006ca620(param_1);
    FUN_00449810(uVar5);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    FUN_006ca620(param_1);
    FID_conflict_operator_(param_2);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

