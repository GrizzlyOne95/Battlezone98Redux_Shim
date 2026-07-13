
void FUN_006b8af0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1f4 [4];
  undefined1 local_1f0 [4];
  undefined1 local_1ec [4];
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  undefined4 local_1d4;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined4 local_1ac;
  undefined1 local_1a5;
  undefined4 local_1a4;
  undefined1 local_19d;
  undefined1 local_19c [88];
  undefined1 local_144 [256];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850fb7;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1ac = param_1;
  local_1a5 = 0x20;
  FUN_006da220(&local_1a4,param_1,param_2,&local_1a5,local_14);
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 != '\0') {
    basic_string<>("Invalid request line1");
    local_8 = 0;
    local_1d4 = basic_string<>();
    local_8._0_1_ = 1;
    local_1cc = local_1d4;
    local_1dc = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    local_1b8 = local_1dc;
    FUN_006b7140(local_44,400,local_1dc,local_1d4);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_144,(ThrowInfo *)&DAT_008d838c);
  }
  local_1c4 = FUN_006da0a0(local_1ac,local_1a4);
  local_8 = 3;
  local_1bc = local_1c4;
  FUN_006b8960(local_1c4);
  local_8 = 0xffffffff;
  ~basic_string<>();
  puVar2 = (undefined4 *)FID_conflict_operator_(local_1f0,1);
  local_1ac = *puVar2;
  local_19d = 0x20;
  puVar2 = (undefined4 *)FUN_006da220(local_1ec,local_1ac,param_2,&local_19d);
  local_1a4 = *puVar2;
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 != '\0') {
    basic_string<>("Invalid request line2");
    local_8 = 4;
    local_1d8 = basic_string<>();
    local_8._0_1_ = 5;
    local_1c8 = local_1d8;
    local_1e0 = basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,6);
    local_1d0 = local_1e0;
    FUN_006b7140(local_2c,400,local_1e0,local_1d8);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_19c,(ThrowInfo *)&DAT_008d838c);
  }
  local_1e8 = FUN_006da0a0(local_1ac,local_1a4);
  local_8 = 7;
  local_1b4 = local_1e8;
  FUN_006b8ad0(local_1e8);
  local_8 = 0xffffffff;
  ~basic_string<>();
  uVar3 = param_2;
  puVar2 = (undefined4 *)FID_conflict_operator_(local_1f4,1);
  local_1e4 = FUN_006da0a0(*puVar2,uVar3);
  local_8 = 8;
  local_1c0 = local_1e4;
  FUN_006b7470(local_1e4);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

