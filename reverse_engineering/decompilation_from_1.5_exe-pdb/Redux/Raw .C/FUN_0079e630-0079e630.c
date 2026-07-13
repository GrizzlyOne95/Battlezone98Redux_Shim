
void FUN_0079e630(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  iVar2 = FUN_006cc050(uVar1);
  if (iVar2 != 2) {
    iVar2 = FUN_006cc050(uVar1);
    if (iVar2 != 4) goto LAB_0079e6f4;
  }
  iVar2 = FUN_007cb0a0();
  if (iVar2 == -1) {
    FUN_00740a90(0);
  }
  else {
    basic_string<>(&DAT_008a1ad8);
    local_8 = 0;
    puVar4 = local_2c;
    puVar3 = (undefined4 *)FUN_004200d0(iVar2);
    FUN_00741990(*puVar3,puVar4);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
LAB_0079e6f4:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

