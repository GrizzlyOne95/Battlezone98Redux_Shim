
undefined4 FUN_007d9b30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_30 [20];
  undefined1 local_1c [20];
  allocator<char> *local_8;
  
  uVar2 = 0;
  uVar1 = FUN_007dafd0(local_30,param_2,param_3,param_4,0);
  FUN_007daff0(uVar1,uVar2);
  puVar3 = local_1c;
  uVar1 = std::allocator<char>::allocator<char>(local_8);
  uVar1 = FUN_007da1f0(uVar1,puVar3);
  FUN_007db010(param_1,uVar1);
  return param_1;
}

