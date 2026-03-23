
void __thiscall
FUN_006b0ae0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined1 param_6)

{
  char cVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501e8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  if (*(char *)(param_1 + 0xd8) == '\0') {
    cVar1 = FUN_006c91e0(param_3,param_5);
    FUN_006acd10(uVar2);
    if (cVar1 != '\0') {
      FUN_006b0530();
    }
    local_8 = 0xffffffff;
    FUN_006c8d50();
  }
  else {
    FUN_006b0660(param_5,param_6);
    local_8 = 0xffffffff;
    FUN_006c8d50();
  }
  ExceptionList = local_10;
  return;
}

