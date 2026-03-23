
void __thiscall FUN_0042a440(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0042df10(param_2,local_14);
  if (cVar1 == '\0') {
    iVar2 = FUN_00840de0();
    basic_string<>(param_2);
    local_8 = 0;
    FUN_0042a3e0(local_2c,param_1);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (iVar2 != 0) {
      FUN_00840e30(iVar2);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

