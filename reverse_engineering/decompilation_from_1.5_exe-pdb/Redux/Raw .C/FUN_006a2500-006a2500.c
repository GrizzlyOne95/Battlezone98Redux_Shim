
void FUN_006a2500(void)

{
  char *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  size_t sVar6;
  undefined8 local_48;
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  char *local_34;
  undefined1 *local_30;
  char *local_2c;
  char *local_28;
  int local_24;
  int local_20;
  undefined *local_1c;
  int local_18;
  undefined4 local_14;
  uint local_10;
  char *local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  local_6 = DAT_008e7732;
  DAT_008e7732 = 0;
  for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
    FUN_006a2340(*(undefined4 *)(&DAT_02c00ee0 + local_10 * 8),
                 *(undefined4 *)(&DAT_02c00ee4 + local_10 * 8));
  }
  local_1c = &DAT_0094e2d4;
  FUN_00422170();
  puVar3 = (undefined4 *)FID_conflict_begin(local_38);
  local_14 = *puVar3;
  while( true ) {
    uVar4 = FID_conflict_end(local_40);
    cVar2 = FID_conflict_operator__(uVar4);
    if (cVar2 == '\0') break;
    piVar5 = (int *)FUN_00421ec0();
    local_20 = *piVar5;
    local_18 = (*(code *)**(undefined4 **)(local_20 + 0x18))();
    if ((*(int *)(local_18 + 0x1c) == 1) || (*(int *)(local_18 + 0x1c) == 6)) {
      FUN_006a2200(local_18,0);
    }
    FUN_0046b260(local_3c,0);
  }
  DAT_02c00edc = FUN_004e0f70(0x61637061,0x726d);
  FUN_006a2200(DAT_02c00edc,0);
  local_24 = FUN_004fbaf0(&DAT_00915540,0x2e);
  if (local_24 == 0) {
    local_c = &DAT_00915540;
    local_30 = &DAT_00915541;
    pcVar1 = local_c;
    do {
      local_c = pcVar1;
      pcVar1 = local_c + 1;
    } while (*local_c != '\0');
    local_34 = local_c + -0x915540;
    local_5 = 0;
    local_28 = local_34;
    local_c = local_c + 1;
  }
  else {
    local_28 = (char *)(local_24 + -0x915540);
  }
  local_2c = local_28;
  local_48 = 0x5f62;
  sVar6 = FUN_0046b550(local_28,6);
  strncpy((char *)((int)&local_48 + 2),&DAT_00915540,sVar6);
  FUN_006a2340((undefined4)local_48,local_48._4_4_);
  local_48 = 0;
  sVar6 = FUN_0046b550(local_2c,8);
  strncpy((char *)&local_48,&DAT_00915540,sVar6);
  FUN_006a2340((undefined4)local_48,local_48._4_4_);
  DAT_008e7732 = local_6;
  return;
}

