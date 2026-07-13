
void FUN_0056ba90(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  int *local_34;
  undefined4 local_30;
  int local_2c;
  int *local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b27e;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00461580(param_1,0);
  local_8 = 0;
  *local_24 = MultDMEvent::vftable;
  vector<>(uVar2);
  local_8._0_1_ = 1;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  local_24[0xd] = 1;
  local_24[0xf] = 0;
  local_24[0x10] = 0;
  local_24[0x11] = 0;
  local_24[6] = 0;
  DAT_00920174 = 0;
  DAT_00920170 = 0;
  FUN_00430590();
  puVar3 = (undefined4 *)FUN_0042d8c0(local_40);
  local_30 = *puVar3;
  while( true ) {
    uVar4 = FID_conflict_begin(local_38);
    cVar1 = FUN_00420f10(uVar4);
    if (cVar1 == '\0') break;
    puVar3 = (undefined4 *)FUN_0042de50();
    local_28 = (int *)*puVar3;
    if ((*local_28 != 0) && (iVar5 = _strnicmp((char *)*local_28,"king",4), iVar5 == 0)) {
      local_24[6] = 1;
      DAT_00920174 = 1;
      iVar5 = isdigit((int)*(char *)(*local_28 + 4));
      if ((iVar5 == 0) && (2 < local_28[1])) {
        local_34 = local_28;
        FUN_0041ff90(&local_34);
      }
      else {
        for (local_2c = 0; local_2c < local_28[1]; local_2c = local_2c + 1) {
          local_20 = *(undefined4 *)(local_28[2] + local_2c * 8);
          local_1c = *(undefined4 *)(local_28[2] + 4 + local_2c * 8);
          iVar5 = atoi((char *)(*local_28 + 4));
          iVar5 = FUN_0043d130(1,iVar5);
          local_18 = (float)iVar5;
          FUN_0056cb00(&local_20);
        }
      }
    }
    FUN_00438c10(local_3c,0);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

