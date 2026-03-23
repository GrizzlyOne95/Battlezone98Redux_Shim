
void FUN_007db220(undefined4 param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_10 [4];
  undefined1 local_c [7];
  allocator<char> local_5;
  
  puVar1 = (undefined1 *)std::allocator<char>::allocator<char>(&local_5);
  uVar2 = FUN_007dcab0(local_c,param_2,*puVar1);
  puVar3 = (undefined4 *)FUN_00770900(local_10,uVar2);
  FUN_007dcae0(*puVar3);
  return;
}

