
void FUN_0046f330(void)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined1 local_34 [12];
  undefined1 local_28 [8];
  undefined4 *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if ((&DAT_0260d6c4)[local_8] != '\0') {
      local_18 = (undefined4 *)(&DAT_0260d640 + local_8 * 4);
      local_20 = (undefined4 *)(&DAT_0260d680 + local_8 * 4);
      local_1c = (undefined4 *)(&DAT_0260d6d8 + local_8 * 4);
      FUN_0046f2c0();
      FUN_0046f2c0();
      FUN_0046f2c0();
      FUN_00430590();
      puVar2 = (undefined4 *)FUN_0042d8c0();
      local_c = *puVar2;
      while( true ) {
        FID_conflict_begin();
        cVar1 = FUN_00420f10();
        if (cVar1 == '\0') break;
        piVar3 = (int *)FUN_0042de50();
        local_10 = *piVar3;
        if ((*(int *)(local_10 + 4) == local_8) && (*(char *)(local_10 + 8) != '\0')) {
          FUN_0046eb60();
          FUN_0046ec90(*(undefined1 *)(local_10 + 9),local_58,local_50,local_48,local_40);
          FUN_0046ee80(*local_18);
          FUN_0046ee80(*local_1c);
        }
        FUN_00438c10(local_28,0);
      }
      puVar2 = (undefined4 *)FUN_0042d8c0();
      local_c = *puVar2;
      while( true ) {
        FID_conflict_begin();
        cVar1 = FUN_00420f10();
        if (cVar1 == '\0') break;
        piVar3 = (int *)FUN_0042de50();
        local_14 = *piVar3;
        if ((*(int *)(local_14 + 4) == local_8) && (*(char *)(local_14 + 8) == '\0')) {
          FUN_0046eb60();
          FUN_0046ec90(*(undefined1 *)(local_14 + 9),local_78,local_70,local_68,local_60);
          FUN_0046ee80(*local_20,*(undefined4 *)(local_14 + 0xc));
        }
        FUN_00438c10(local_34,0);
      }
    }
  }
  DAT_0260d111 = 0;
  return;
}

