
void FUN_007476a0(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 local_1c0 [16];
  undefined1 local_1b0 [16];
  undefined1 local_1a0 [4];
  undefined1 local_19c [4];
  undefined1 local_198 [4];
  undefined4 local_194;
  undefined4 local_190;
  int local_18c;
  int local_188;
  int local_184;
  undefined4 local_180;
  int local_17c;
  int *local_178;
  undefined1 local_174 [24];
  undefined1 local_15c [24];
  undefined1 local_144 [24];
  undefined1 local_12c [24];
  char local_114 [128];
  char local_94 [128];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b8fc;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_188 = FUN_0056f900(local_14);
  local_17c = FUN_0073bd10();
  if ((local_188 != 0) && (local_17c != 0)) {
    local_184 = 0;
    local_18c = 0;
    puVar2 = (undefined4 *)FUN_0042d8c0(local_1a0);
    local_180 = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_begin(local_198);
    local_194 = *puVar2;
    cVar1 = FUN_00420f10(&local_194);
    if (cVar1 != '\0') {
      iVar3 = FUN_004305e0();
      if (*(int *)(iVar3 + 0x90) != 0) {
        local_18c = local_18c + 1;
        iVar3 = FUN_004305e0();
        if (*(char *)(iVar3 + 0x8c) == '\0') {
          puVar2 = (undefined4 *)FUN_0042d8c0(local_19c);
          local_190 = *puVar2;
          cVar1 = FUN_00420f10(&local_194);
          if (cVar1 != '\0') {
            iVar3 = FUN_004305e0();
            iVar4 = FUN_004305e0();
            if (*(int *)(iVar3 + 0x90) == *(int *)(iVar4 + 0x90)) {
              cVar1 = FUN_00420f10(&local_180);
              if (cVar1 != '\0') {
                local_184 = local_184 + 1;
                goto LAB_00747856;
              }
            }
                    /* WARNING: Subroutine does not return */
            FUN_0042de70();
          }
        }
      }
LAB_00747856:
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    if (*(int *)(local_17c + 0x84) != local_18c) {
      *(int *)(local_17c + 0x84) = local_18c;
      sprintf(local_94,"%ld",*(undefined4 *)(local_17c + 0x84));
      basic_string<>(local_94);
      local_8 = 0;
      basic_string<>("clientsconnected");
      local_8._0_1_ = 1;
      puVar7 = local_144;
      puVar6 = local_12c;
      uVar5 = FUN_0073bcf0(local_1c0);
      (**(code **)(*local_178 + 0x1c))(uVar5,puVar6,puVar7);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    if (*(int *)(local_17c + 0x88) != local_184) {
      *(int *)(local_17c + 0x88) = local_184;
      sprintf(local_114,"%ld",*(undefined4 *)(local_17c + 0x88));
      basic_string<>(local_114);
      local_8 = 2;
      basic_string<>("clientsremotedup");
      local_8._0_1_ = 3;
      puVar7 = local_15c;
      puVar6 = local_174;
      uVar5 = FUN_0073bcf0(local_1b0);
      (**(code **)(*local_178 + 0x1c))(uVar5,puVar6,puVar7);
      local_8 = CONCAT31(local_8._1_3_,2);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  FUN_0079d6f0();
  FUN_00795cd0();
  FUN_007a4880();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

