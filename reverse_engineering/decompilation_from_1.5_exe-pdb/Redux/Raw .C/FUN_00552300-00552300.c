
undefined * __fastcall FUN_00552300(undefined4 param_1)

{
  char cVar1;
  undefined *puVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084b05e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc3050 & 1) == 0) {
    DAT_02cc3050 = DAT_02cc3050 | 1;
    local_8 = 0;
    FUN_00422260(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
    FUN_0083e979(FUN_00866e10);
  }
  local_8 = 0xffffffff;
  cVar1 = FUN_004202c0();
  if (cVar1 == '\0') {
    puVar2 = &DAT_02cc3048;
  }
  else {
    puVar2 = (undefined *)FUN_0045c660();
  }
  ExceptionList = local_10;
  return puVar2;
}

