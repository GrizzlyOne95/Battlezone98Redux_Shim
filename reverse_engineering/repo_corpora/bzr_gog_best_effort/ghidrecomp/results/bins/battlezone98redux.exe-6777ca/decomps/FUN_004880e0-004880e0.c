
undefined * FUN_004880e0(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  byte in_stack_0000001c;
  undefined1 local_28 [4];
  undefined *local_24;
  undefined *local_20;
  undefined *local_1c;
  undefined *local_18;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00848ee6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  if ((DAT_02cc2f1c & 1) == 0) {
    DAT_02cc2f1c = DAT_02cc2f1c | 1;
    local_8._0_1_ = 1;
    local_8._1_3_ = 0;
    FUN_00482d60(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_0083e979(FUN_00866870);
    local_8 = (uint)local_8._1_3_ << 8;
  }
  FUN_00420350(local_14,&stack0x00000004);
  uVar2 = FID_conflict_begin(local_28);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    FUN_00422150();
    iVar3 = size();
    if (iVar3 == 0) {
      local_1c = &DAT_02cc2e50;
      local_8 = 0xffffffff;
      ~basic_string<>();
      local_18 = local_1c;
    }
    else {
      FUN_00422150();
      uVar4 = size();
      if (in_stack_0000001c < uVar4) {
        uVar4 = (uint)in_stack_0000001c;
        FUN_00422150(uVar4);
        puVar5 = (undefined4 *)FUN_004200d0(uVar4);
        local_24 = (undefined *)*puVar5;
        local_8 = 0xffffffff;
        ~basic_string<>();
        local_18 = local_24;
      }
      else {
        FUN_00422150();
        iVar3 = size();
        iVar3 = iVar3 + -1;
        FUN_00422150(iVar3);
        puVar5 = (undefined4 *)FUN_004200d0(iVar3);
        local_20 = (undefined *)*puVar5;
        local_8 = 0xffffffff;
        ~basic_string<>();
        local_18 = local_20;
      }
    }
  }
  else {
    local_18 = &DAT_02cc2e50;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  return local_18;
}

