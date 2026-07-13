
void FUN_006fa2c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  allocator<char> local_14 [16];
  
  FUN_00703ba0(param_2);
  uVar1 = FUN_006d6170(param_5);
  uVar1 = FUN_006d0d10(uVar1);
  uVar1 = FUN_006b3f60(param_4,uVar1);
  uVar2 = std::allocator<char>::allocator<char>(local_14);
  FUN_006af320(*param_1,*(undefined1 *)(param_1 + 1),uVar2,uVar1);
  return;
}

