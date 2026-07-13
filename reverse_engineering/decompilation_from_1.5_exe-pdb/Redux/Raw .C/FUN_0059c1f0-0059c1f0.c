
void FUN_0059c1f0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_70 [4];
  char *local_6c;
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  int local_60;
  float local_5c;
  char *local_58;
  char *local_50;
  undefined4 local_4c;
  int *local_48;
  char *local_44;
  char *local_40;
  char local_39;
  undefined4 *local_38;
  char local_34 [16];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c160;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00461580(param_1,0);
  local_8 = 0;
  *local_38 = PathSpawn::vftable;
  local_38[6] = 0;
  memset(local_38 + 7,0,0x1130);
  FUN_00430590(uVar2);
  local_38[0x453] = 0;
  puVar3 = (undefined4 *)FUN_0042d8c0(local_70);
  local_4c = *puVar3;
  while ((uint)local_38[0x453] < 100) {
    uVar4 = FID_conflict_begin(local_64);
    cVar1 = FUN_00420f10(uVar4);
    if (cVar1 == '\0') break;
    puVar3 = (undefined4 *)FUN_0042de50();
    local_48 = (int *)*puVar3;
    if (((*local_48 != 0) && (iVar5 = _stricmp((char *)*local_48,"edge_path"), iVar5 != 0)) &&
       (iVar5 = _strnicmp((char *)*local_48,"path_",5), iVar5 != 0)) {
      local_40 = (char *)*local_48;
      for (local_44 = (char *)(local_38 + local_38[0x453] * 0xb + 0xf);
          ((*local_40 != '_' && (*local_40 != '\0')) &&
          (local_44 < (char *)((int)local_38 + local_38[0x453] * 0x2c + 0x45)));
          local_44 = local_44 + 1) {
        *local_44 = *local_40;
        local_40 = local_40 + 1;
      }
      *local_44 = '\0';
      local_44 = local_44 + 1;
      sprintf(local_24,"%s.odf",local_38 + local_38[0x453] * 0xb + 0xf);
      iVar5 = FUN_00481f10(local_24);
      if (iVar5 != 0) {
        FUN_00589430(local_24);
        local_8._0_1_ = 1;
        FUN_0047b6c0(0xd3dd9cec,0x92d04727,local_34,0);
        if (local_34[0] == '\0') {
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_00589530();
        }
        else {
          local_58 = (char *)*local_48;
          local_6c = (char *)(local_38 + local_38[0x453] * 0xb + 10);
          local_50 = local_6c;
          do {
            local_39 = *local_58;
            *local_50 = local_39;
            local_58 = local_58 + 1;
            local_50 = local_50 + 1;
          } while (local_39 != '\0');
          if (*local_40 == '_') {
            local_40 = local_40 + 1;
            local_60 = atoi(local_40);
            if (local_60 < 1) {
              local_5c = 10.0;
            }
            else {
              local_5c = (float)local_60;
            }
            local_38[local_38[0x453] * 0xb + 9] = local_5c;
          }
          local_38[0x453] = local_38[0x453] + 1;
          local_8 = (uint)local_8._1_3_ << 8;
          FUN_00589530();
        }
      }
    }
    FUN_00438c10(local_68,0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

