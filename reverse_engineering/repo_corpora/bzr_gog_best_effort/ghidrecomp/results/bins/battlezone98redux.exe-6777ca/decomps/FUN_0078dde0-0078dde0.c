
void __fastcall FUN_0078dde0(int param_1)

{
  void *pvVar1;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x15c) == 0) {
    pvVar1 = operator_new(0x144);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007d1cc0("movie",0x42b40000,0x43e40000,0x449d8000,0x432e0000,0x20,
                              *(undefined4 *)(param_1 + 0x158),0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x15c) = local_1c;
    FUN_007d3850("bzone.ogv",0);
    FUN_007d3dd0(1);
    FUN_007d2110(*(undefined4 *)(param_1 + 0x15c),0);
  }
  ExceptionList = local_10;
  return;
}

