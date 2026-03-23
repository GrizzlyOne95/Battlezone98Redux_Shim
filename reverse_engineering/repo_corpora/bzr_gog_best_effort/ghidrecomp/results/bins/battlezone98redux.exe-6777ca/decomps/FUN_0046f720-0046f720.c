
char FUN_0046f720(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_c [7];
  char local_5;
  
  local_5 = FUN_004ccd10(param_1,"[AOIs]");
  if (local_5 != '\0') {
    local_10 = 0;
    FUN_0042d8c0(local_c);
    while (local_5 != '\0') {
      uVar2 = FID_conflict_begin(local_20);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_0042de50();
      if (*(char *)(*piVar3 + 0x14) == '\0') {
        local_10 = local_10 + 1;
      }
      FUN_00438c10(local_1c,0);
    }
    local_5 = FUN_004cd1b0(param_1,&local_10,4,&DAT_00874054);
    if (local_5 != '\0') {
      FUN_0042d8c0(local_14);
      while (local_5 != '\0') {
        uVar2 = FID_conflict_begin(local_28);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 == '\0') {
          return local_5;
        }
        puVar4 = (undefined4 *)FUN_0042de50();
        local_18 = *puVar4;
        local_5 = FUN_0046f940(param_1);
        FUN_00438c10(local_24,0);
      }
    }
  }
  return local_5;
}

