
void FUN_00736890(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 local_28 [4];
  undefined4 local_24;
  int local_20;
  uint local_1c;
  int local_18;
  undefined1 local_14 [4];
  uint local_10;
  uint local_c;
  allocator<char> *local_8;
  
  local_10 = FUN_007375f0(param_1,param_2);
  local_1c = FUN_00732ba0();
  if (local_1c < local_10) {
    local_c = 0;
    piVar2 = (int *)std::allocator<char>::allocator<char>(local_8);
    local_18 = *piVar2;
    local_c = local_10;
    local_24 = FUN_00732c20(3,local_10,&local_c,&local_18);
    if (local_18 == 0) {
      piVar2 = (int *)std::allocator<char>::allocator<char>(local_8);
      local_20 = *piVar2;
      if (local_20 != 0) {
        FUN_00730aa0();
        iVar4 = local_20;
        uVar5 = local_1c;
        std::allocator<char>::allocator<char>(local_8);
        FUN_00417180(iVar4,uVar5);
      }
      FUN_00700920(&local_24);
      FUN_00700940(&local_c);
      *(undefined4 *)(local_8 + 4) = 0;
      FUN_00737610(param_1,param_2);
      return;
    }
    FUN_00700940(&local_c);
  }
  FUN_006cc6f0(local_14);
  FUN_006cc720(local_28);
  while ((cVar1 = FUN_006cc7a0(&param_1,&param_2), cVar1 != '\0' &&
         (cVar1 = FUN_006cc7a0(local_14,local_28), cVar1 != '\0'))) {
    uVar3 = FUN_00422e60();
    get(uVar3);
    FUN_00736ea0(uVar3);
    FUN_006cc780();
    FUN_006cc780();
  }
  cVar1 = eq_int_type(&param_1,&param_2);
  if (cVar1 == '\0') {
    FUN_00737610(param_1,param_2);
  }
  else {
    iVar4 = FUN_00416410();
    FUN_00732bc0(iVar4 - local_10);
  }
  return;
}

