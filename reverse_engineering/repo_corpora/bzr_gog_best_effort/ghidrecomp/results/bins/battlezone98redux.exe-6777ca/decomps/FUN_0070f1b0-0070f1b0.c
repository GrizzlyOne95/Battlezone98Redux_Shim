
/* WARNING: Removing unreachable block (ram,0x0070f1fe) */

void FUN_0070f1b0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_c8 [8];
  undefined1 local_c0 [8];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined4 local_b0;
  undefined4 local_ac;
  undefined1 local_a8 [12];
  undefined4 local_9c;
  int local_98;
  char local_91;
  uint local_90;
  undefined1 local_8c [32];
  undefined1 local_6c [32];
  undefined1 local_4c [24];
  undefined4 local_34;
  undefined4 local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008579fe;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_90 = 0;
  FUN_006e48d0(local_14);
  local_8 = 0;
  vector<>();
  local_8._0_1_ = 1;
  basic_string<>("Sec-WebSocket-Extensions");
  local_8._0_1_ = 2;
  local_91 = FUN_006b74f0(local_6c,local_a8);
  local_8._0_1_ = 1;
  ~basic_string<>();
  if (local_91 == '\0') {
    iVar3 = FUN_006e6090();
    if (iVar3 == 0) {
      FUN_0071a530(&local_34);
      local_90 = local_90 | 1;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00704c70();
      local_8 = 0xffffffff;
      FUN_006e4470();
    }
    else {
      FUN_00423890();
      cVar1 = FUN_0044bb90();
      if (cVar1 != '\0') {
        FUN_006e48d0();
        local_8 = CONCAT31(local_8._1_3_,3);
        puVar2 = (undefined4 *)FID_conflict_begin(local_b8);
        local_9c = *puVar2;
        while( true ) {
          uVar4 = FID_conflict_end(local_b4);
          cVar1 = FID_conflict_operator__(uVar4);
          if (cVar1 == '\0') break;
          uVar4 = FUN_00422220("permessage-deflate");
          cVar1 = FUN_00427270(uVar4);
          if ((cVar1 != '\0') && (cVar1 = FUN_0044bb90(), cVar1 == '\0')) {
            iVar3 = FUN_00422220();
            local_b0 = FUN_00710710(local_8c,iVar3 + 0x18);
            local_8._0_1_ = 4;
            local_ac = local_b0;
            FUN_007100a0(local_b0);
            local_8 = CONCAT31(local_8._1_3_,3);
            FUN_006e4470();
            cVar1 = FUN_006ab7d0();
            if (cVar1 == '\0') {
              FUN_00449810(local_4c);
              FUN_007107b0(local_c8,*(undefined1 *)(local_98 + 5));
            }
          }
          FUN_006cc780();
        }
        local_8._0_1_ = 1;
        FUN_006e4470();
      }
      FUN_0071a530(&local_34);
      local_90 = local_90 | 1;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00704c70();
      local_8 = 0xffffffff;
      FUN_006e4470();
    }
  }
  else {
    puVar2 = (undefined4 *)make_error_code(local_c0,0x1c);
    local_34 = *puVar2;
    local_30 = puVar2[1];
    FUN_0071a530(&local_34);
    local_90 = local_90 | 1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00704c70();
    local_8 = 0xffffffff;
    FUN_006e4470();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

