
void FUN_0074d110(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_40 [24];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [11];
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bd98;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_00945460 == '\x01') {
    iVar2 = get(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    if (*(char *)(iVar2 + 9) != '\0') {
      DAT_00945460 = '\0';
      uVar3 = FUN_00416410();
      FUN_00740e70(uVar3);
    }
  }
  FUN_00428520();
  local_8 = 0;
  FUN_0074d2f0(&DAT_0260b178);
  FUN_00424640(local_1c);
  FID_conflict_begin(local_20);
  while( true ) {
    cVar1 = FUN_00420f10(local_20);
    if (cVar1 == '\0') break;
    uVar3 = FUN_004237d0();
    FUN_0073a740(uVar3);
    FUN_00578c20(local_24,local_40);
    local_11 = 1;
    uVar3 = FID_conflict_begin(local_28);
    cVar1 = FUN_004221b0(uVar3);
    if (cVar1 != '\0') {
      local_11 = 0;
    }
    FUN_00741b20(local_40,local_40,local_11);
    FUN_00422190();
  }
  local_8 = 0xffffffff;
  FUN_0045c7d0();
  ExceptionList = local_10;
  return;
}

