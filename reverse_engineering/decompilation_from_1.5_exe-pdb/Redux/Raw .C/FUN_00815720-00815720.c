
undefined4 FUN_00815720(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  allocator<char> *local_c;
  undefined1 local_5;
  
  uVar6 = param_4;
  uVar1 = FUN_006d0a70(&local_5);
  uVar5 = extraout_ECX;
  FUN_006d1160(uVar1);
  uVar4 = param_3;
  uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)&param_2);
  uVar1 = extraout_ECX_00;
  FUN_006cc200(uVar2);
  puVar3 = local_18;
  std::allocator<char>::allocator<char>(local_c);
  FUN_00815b50(puVar3,uVar1,uVar4,uVar5,uVar6);
  puVar3 = local_14;
  puVar7 = puVar3;
  FUN_006cc200(local_18);
  uVar1 = FUN_006d0c50(puVar3);
  FUN_00815be0(uVar1,puVar7);
  return param_1;
}

