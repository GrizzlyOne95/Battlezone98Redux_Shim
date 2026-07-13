
undefined4 FUN_006a61b0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = *(int *)(DAT_00920f04 + param_2 * 4);
  if (iVar1 == 0) {
    local_1c = 0;
  }
  else {
    pvVar2 = operator_new(0x58);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00697340(param_1,param_3,1,1,0x466a6000,DAT_00920f04,iVar1);
    }
  }
  ExceptionList = local_10;
  return local_1c;
}

