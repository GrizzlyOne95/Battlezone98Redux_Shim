
void FUN_007573b0(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int local_70;
  int local_6c;
  undefined1 local_64 [80];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c558;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (param_1 != param_2) {
    local_6c = param_1;
    while (iVar4 = local_6c + 0x50, iVar4 != param_2) {
      uVar3 = FUN_00417780(iVar4,uVar2);
      FUN_00756b80(uVar3);
      local_8 = 0;
      cVar1 = FUN_00754c60(local_64,param_1);
      local_70 = iVar4;
      if (cVar1 == '\0') {
        while( true ) {
          local_70 = local_70 + -0x50;
          cVar1 = FUN_00754c60(local_64,local_70);
          if (cVar1 == '\0') break;
          uVar3 = FUN_00417780(local_70);
          FUN_007575c0(uVar3);
        }
        uVar3 = FUN_00417780(local_64);
        FUN_007575c0(uVar3);
      }
      else {
        _Move<>(param_1,iVar4,local_6c + 0xa0);
        uVar3 = FUN_00417780(local_64);
        FUN_007575c0(uVar3);
      }
      local_8 = 0xffffffff;
      FUN_007538f0();
      local_6c = iVar4;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

