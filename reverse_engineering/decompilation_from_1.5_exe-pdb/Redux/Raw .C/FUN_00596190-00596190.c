
void FUN_00596190(char param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  undefined4 local_14;
  undefined *local_10;
  int *local_c;
  undefined4 local_8;
  
  local_10 = &DAT_0094de1c;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_1c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_24);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_0042de50();
    local_c = (int *)*puVar2;
    if ((param_1 != '\0') || (*local_c != 0)) {
      if (*local_c == 0) {
        local_14 = DAT_00917558;
      }
      else {
        local_14 = DAT_0091755c;
      }
      FUN_00595e80(local_c,0xffffffff,local_14);
    }
    FUN_00438c10(local_20,0);
  }
  return;
}

