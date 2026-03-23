
void FUN_006e8f50(int param_1,undefined4 param_2)

{
  char cVar1;
  char *pcStack_98;
  char *pcStack_94;
  uint uStack_90;
  undefined1 local_70 [8];
  undefined4 local_68;
  undefined4 local_64;
  int local_4c;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008548c0;
  local_10 = ExceptionList;
  uStack_90 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_90;
  ExceptionList = &local_10;
  pcStack_94 = (char *)0x400;
  pcStack_98 = (char *)0x6e8f95;
  local_18 = uStack_90;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_94 = "connection handle_terminate";
    pcStack_98 = (char *)0x400;
    FUN_006d08b0();
  }
  pcStack_94 = (char *)0x6e8fbc;
  cVar1 = FUN_006ab7d0();
  if (cVar1 != '\0') {
    pcStack_94 = (char *)param_2;
    pcStack_98 = "handle_terminate";
    FUN_006f90a0(1);
  }
  if (param_1 == 1) {
    pcStack_94 = (char *)0x15;
    pcStack_98 = (char *)0x6e8fe6;
    FUN_006eac90();
    pcStack_94 = local_70;
    pcStack_98 = (char *)0x6e8ff8;
    cVar1 = FUN_006ab800();
    if (cVar1 != '\0') {
      pcStack_94 = (char *)0x6e900d;
      cVar1 = FUN_006caba0();
      if (cVar1 != '\0') {
        local_64 = shared_ptr<>(local_4c + 0x918);
        FUN_006e6250();
      }
    }
  }
  else if (param_1 == 2) {
    pcStack_94 = (char *)0x6e9052;
    cVar1 = FUN_006caba0();
    if (cVar1 != '\0') {
      shared_ptr<>(local_4c + 0x918);
      FUN_006e6250();
    }
    pcStack_94 = (char *)0x6e908b;
    FUN_006f8d30();
  }
  else {
    pcStack_94 = "Unknown terminate_status";
    pcStack_98 = (char *)0x10;
    FUN_006d47b0();
  }
  pcStack_94 = (char *)0x6e90b0;
  cVar1 = FUN_006caba0();
  if (cVar1 == '\0') {
    ExceptionList = local_10;
    FUN_0083e885();
    return;
  }
  local_8 = 0;
  local_68 = FUN_006e1540(&pcStack_98);
  FUN_006f2dd0();
  FUN_006e915d();
  return;
}

