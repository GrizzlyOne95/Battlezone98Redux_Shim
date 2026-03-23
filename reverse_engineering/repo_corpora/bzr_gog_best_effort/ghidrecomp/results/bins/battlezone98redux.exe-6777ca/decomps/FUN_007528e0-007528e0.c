
undefined4 __fastcall FUN_007528e0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085c108;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = 0;
  while( true ) {
    FUN_00764790(uVar2,param_1);
    uVar3 = FUN_004170c0();
    if (uVar3 <= local_18) {
      local_8 = 0xffffffff;
      ~basic_string<>();
      ExceptionList = local_10;
      return 0;
    }
    uVar3 = local_18;
    FUN_00764790(local_18,&stack0x00000004);
    uVar4 = FUN_00752d30(uVar3);
    cVar1 = FUN_00427310(uVar4);
    if (cVar1 != '\0') break;
    local_18 = local_18 + 1;
  }
  FUN_00764790(local_18);
  uVar4 = FUN_00752d30(local_18);
  FUN_007529c0(uVar4);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return 1;
}

