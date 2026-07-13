
undefined4 FUN_006ee350(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_30 [8];
  undefined1 local_28 [4];
  char local_24;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  allocator<char> *local_c;
  undefined1 local_5;
  
  local_14 = param_2;
  puVar4 = local_30;
  uVar1 = FUN_006d0a70(&local_5);
  uVar3 = extraout_ECX;
  FUN_006d1160(uVar1);
  puVar2 = local_28;
  uVar1 = local_14;
  std::allocator<char>::allocator<char>(local_c);
  FUN_006fb990(puVar2,uVar1,uVar3,puVar4);
  if (local_24 == '\0') {
    uVar1 = extraout_ECX_00;
    FUN_006cc200(local_28);
    local_10 = FUN_006d0c50(uVar1);
  }
  else {
    puVar4 = local_30;
    uVar1 = FUN_00417780(param_2,puVar4);
    local_10 = FUN_006fba10(local_1c,uVar1,puVar4);
  }
  local_18 = local_10;
  FUN_006cc240(local_10);
  return param_1;
}

