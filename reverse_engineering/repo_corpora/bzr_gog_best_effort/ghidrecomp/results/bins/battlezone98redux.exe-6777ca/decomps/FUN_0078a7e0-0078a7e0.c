
void FUN_0078a7e0(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_34 [12];
  undefined4 local_28;
  int local_24;
  int local_20;
  int *local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e928;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_20 = FUN_007cb0a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (local_20 != -1) {
    FUN_00764760();
    local_24 = FUN_0056f900();
    if (local_24 == 0) {
      vector<>();
      local_8 = 0;
      local_28 = 1;
      FUN_0041ff90(&local_28);
      FUN_007c7aa0(local_34);
      FUN_005d4260();
      FUN_00764760();
      FUN_0073ddf0();
      local_8 = 0xffffffff;
      FUN_0041fe20();
    }
    else {
      local_18 = (int *)FUN_007647a0();
      local_14 = 0;
      while (uVar2 = FUN_007564f0(), local_14 < uVar2) {
        iVar3 = FUN_0078ae80(local_14);
        uVar4 = FUN_007cb100(iVar3 + 0x18);
        cVar1 = FUN_00427310(uVar4);
        if (cVar1 != '\0') break;
        local_14 = local_14 + 1;
      }
      iVar3 = FUN_0078ae80(local_14);
      *(undefined1 *)(iVar3 + 0x48) = 1;
      iVar3 = FUN_0078ae80(local_14);
      (**(code **)(*local_18 + 0x10))(iVar3 + 8);
      FUN_0078a940();
    }
  }
  ExceptionList = local_10;
  return;
}

