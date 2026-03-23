
void FUN_00676670(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int local_38;
  int local_34;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (param_1 != param_2) {
    local_34 = param_1;
    while (iVar4 = local_34 + 0x18, iVar4 != param_2) {
      uVar3 = FUN_00417780(iVar4,uVar2);
      basic_string<>(uVar3);
      local_8 = 0;
      cVar1 = FUN_00422f40(local_2c,param_1);
      local_38 = iVar4;
      if (cVar1 == '\0') {
        while( true ) {
          local_38 = local_38 + -0x18;
          cVar1 = FUN_00422f40(local_2c,local_38);
          if (cVar1 == '\0') break;
          uVar3 = FUN_00417780(local_38);
          FUN_0045e0f0(uVar3);
        }
        uVar3 = FUN_00417780(local_2c);
        FUN_0045e0f0(uVar3);
      }
      else {
        _Move<>(param_1,iVar4,local_34 + 0x30);
        uVar3 = FUN_00417780(local_2c);
        FUN_0045e0f0(uVar3);
      }
      local_8 = 0xffffffff;
      ~basic_string<>();
      local_34 = iVar4;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

