
char FUN_00461d90(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  char local_5;
  
  FUN_00430590();
  local_5 = FUN_004ccd10(param_1,"[AiTasks]");
  if (local_5 != '\0') {
    local_10 = 0;
    if (DAT_0091737c != 0) {
      puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
      local_c = *puVar2;
      while (local_5 != '\0') {
        uVar3 = FID_conflict_begin(local_20);
        cVar1 = FUN_00420f10(uVar3);
        if (cVar1 == '\0') break;
        piVar4 = (int *)FUN_0042de50();
        if (*(char *)(*piVar4 + 4) == '\0') {
          local_10 = local_10 + 1;
        }
        FUN_00438c10(local_1c,0);
      }
    }
    local_5 = FUN_004cd1b0(param_1,&local_10,4,"count");
    if (DAT_0091737c != 0) {
      puVar2 = (undefined4 *)FUN_0042d8c0(local_24);
      local_c = *puVar2;
      while (local_5 != '\0') {
        uVar3 = FID_conflict_begin(local_2c);
        cVar1 = FUN_00420f10(uVar3);
        if (cVar1 == '\0') {
          return local_5;
        }
        puVar2 = (undefined4 *)FUN_0042de50();
        local_14 = *puVar2;
        local_5 = FUN_005d7580(param_1,local_14);
        FUN_00438c10(local_28,0);
      }
    }
  }
  return local_5;
}

