
undefined1 FUN_004cc780(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  undefined1 local_10 [4];
  undefined4 *local_c;
  undefined1 local_5;
  
  local_5 = 1;
  if (DAT_00917a5c != 0) {
    FUN_0042d8c0(local_10);
    while( true ) {
      uVar2 = FID_conflict_begin(local_34);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_0042de50();
      local_c = (undefined4 *)*piVar3;
      if (local_c[1] != 0) {
        local_14 = FUN_004cca70(local_c[1]);
        *(int *)*local_c = local_14;
        if (local_14 == 0) {
          if (0x7dd < DAT_00917b20) {
            local_5 = 0;
          }
          FUN_004cc540(local_c[2],local_c[1]);
        }
      }
      local_20 = local_c;
      local_18 = local_c;
      if (local_c == (undefined4 *)0x0) {
        local_24 = 0;
      }
      else {
        local_24 = FUN_004cc8b0(1);
      }
      FUN_00438c10(local_30,0);
    }
    local_28 = DAT_00917a5c;
    local_1c = DAT_00917a5c;
    if (DAT_00917a5c == 0) {
      local_2c = 0;
    }
    else {
      local_2c = FUN_004cc8e0(1);
    }
    DAT_00917a5c = 0;
    FUN_004cc9c0();
  }
  return local_5;
}

