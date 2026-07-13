
void __thiscall
FUN_0070ae40(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  char cVar2;
  int *piVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008501e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  piVar3 = (int *)(param_1 + 0x24);
  LOCK();
  iVar1 = *piVar3;
  *piVar3 = *piVar3;
  UNLOCK();
  if (iVar1 == 0) {
    FUN_006c8ce0(param_1 + 0x38);
    local_8 = 0;
    cVar2 = Statistics(param_3,param_4,param_5);
    FUN_006acd10();
    if (cVar2 != '\0') {
      FUN_006adef0();
    }
    local_8 = 0xffffffff;
    FUN_006c8d50();
  }
  else {
    FUN_006acd90(param_5,0);
  }
  ExceptionList = local_10;
  return;
}

