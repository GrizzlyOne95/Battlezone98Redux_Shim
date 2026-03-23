
void FUN_00675e20(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int local_3c;
  int local_38;
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ef88;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (param_1 != param_2) {
    local_38 = param_1;
    while (iVar4 = local_38 + 0x1c, iVar4 != param_2) {
      uVar3 = FUN_00417780(iVar4,uVar2);
      FUN_00676860(uVar3);
      local_8 = 0;
      cVar1 = FUN_00669260(local_30,param_1);
      local_3c = iVar4;
      if (cVar1 == '\0') {
        while( true ) {
          local_3c = local_3c + -0x1c;
          cVar1 = FUN_00669260(local_30,local_3c);
          if (cVar1 == '\0') break;
          uVar3 = FUN_00417780(local_3c);
          FUN_00676410(uVar3);
        }
        uVar3 = FUN_00417780(local_30);
        FUN_00676410(uVar3);
      }
      else {
        _Move<>(param_1,iVar4,local_38 + 0x38);
        uVar3 = FUN_00417780(local_30);
        FUN_00676410(uVar3);
      }
      local_8 = 0xffffffff;
      FUN_00430250();
      local_38 = iVar4;
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

