
void __fastcall FUN_007c1780(int param_1)

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
  if (*(int *)(param_1 + 0x150) == 0) {
    pvVar1 = operator_new(0x144);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007d1cc0("movie",0x440dc000,0x42aa0000,0x439b0000,0x43eb0000,0x20,
                              *(undefined4 *)(param_1 + 0x14c),0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x150) = local_1c;
    FUN_007d3f20(10);
    FUN_007d3850("posters.ogv",0);
    FUN_007d2110(*(undefined4 *)(param_1 + 0x150),0);
  }
  ExceptionList = local_10;
  return;
}

