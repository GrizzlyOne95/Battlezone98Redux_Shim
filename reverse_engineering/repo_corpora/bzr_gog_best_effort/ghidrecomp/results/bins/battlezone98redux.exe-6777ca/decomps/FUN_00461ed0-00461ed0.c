
char FUN_00461ed0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined4 local_c;
  char local_5;
  
  local_5 = '\x01';
  if (DAT_0091737c != 0) {
    FUN_00430590();
    puVar2 = (undefined4 *)FUN_0042d8c0(local_14);
    local_c = *puVar2;
    while (local_5 != '\0') {
      uVar3 = FID_conflict_begin(local_1c);
      cVar1 = FUN_00420f10(uVar3);
      if (cVar1 == '\0') {
        return local_5;
      }
      puVar2 = (undefined4 *)FUN_0042de50();
      local_10 = (int *)*puVar2;
      local_5 = (**(code **)(*local_10 + 8))();
      FUN_00438c10(local_18,0);
    }
  }
  return local_5;
}

