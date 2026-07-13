
void FUN_006e6f50(void)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  error_condition *in_stack_00000024;
  undefined4 uStack_38;
  error_condition local_24 [8];
  undefined4 local_1c;
  undefined1 *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00853220;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  uStack_38 = 0x6e6f89;
  FUN_006de390();
  uStack_38 = 0x6e6f95;
  bVar1 = std::error_condition::operator==(in_stack_00000024,local_24);
  if (bVar1) {
LAB_006e6fd4:
    uStack_38 = 0x400;
    FUN_006d08b0();
    local_8 = local_8 & 0xffffff00;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x0000000c);
  }
  else {
    cVar2 = FUN_006ab7d0();
    if (cVar2 != '\0') {
      uStack_38 = 0x6e6fb7;
      FUN_00421ec0();
      uStack_38 = 0x6e6fbe;
      puVar3 = (undefined4 *)FUN_006d7120();
      uStack_38 = *puVar3;
      cVar2 = FUN_006de530();
      if (cVar2 != '\0') goto LAB_006e6fd4;
    }
    cVar2 = FUN_006ab7d0();
    if (cVar2 != '\0') {
      FUN_00421ec0();
      FUN_006d70d0();
    }
    uStack_38 = 0x6e7037;
    cVar2 = FUN_006d4590();
    if (cVar2 != '\0') {
      uStack_38 = 0x400;
      FUN_006d08b0();
    }
    cVar2 = FUN_006caba0();
    if (cVar2 != '\0') {
      local_18 = (undefined1 *)&uStack_38;
      local_1c = shared_ptr<>(local_14 + 0x70);
      FUN_006e6250();
    }
    uStack_38 = 0x6e709b;
    FUN_006cadd0();
    local_8 = local_8 & 0xffffff00;
    FUN_006ca8c0();
    local_8 = 0xffffffff;
    std::function<void___cdecl(void)>::~function<void___cdecl(void)>
              ((function<void___cdecl(void)> *)&stack0x0000000c);
  }
  ExceptionList = local_10;
  return;
}

