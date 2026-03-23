
void FUN_006cfad0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852d98;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0(local_14);
  if (cVar1 == '\0') {
    FUN_006d08b0(1,"Successful connection");
    FUN_00421ec0();
    FUN_006db160();
  }
  else {
    FUN_00421ec0(param_3);
    FUN_006daf10(param_3);
    uVar2 = FUN_006ab780(local_44);
    local_8._0_1_ = 1;
    uVar2 = FUN_006dd7f0(local_2c,"handle_connect error: ",uVar2);
    local_8._0_1_ = 2;
    FUN_006d46a0(0x10,uVar2);
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
  }
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

