
undefined4 FUN_007d99a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_10 [4];
  allocator<char> *local_c;
  undefined1 local_8 [4];
  
  uVar2 = 0;
  uVar1 = FUN_007dada0(local_10,param_2,param_3,param_4,0);
  FUN_007dadc0(uVar1,uVar2);
  puVar3 = local_8;
  uVar1 = std::allocator<char>::allocator<char>(local_c);
  uVar1 = FUN_007da110(uVar1,puVar3);
  FUN_007dade0(param_1,uVar1);
  return param_1;
}

