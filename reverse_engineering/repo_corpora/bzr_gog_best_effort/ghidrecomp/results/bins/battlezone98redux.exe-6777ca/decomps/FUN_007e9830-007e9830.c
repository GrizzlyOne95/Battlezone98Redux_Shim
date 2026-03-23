
undefined1 * __thiscall FUN_007e9830(undefined1 *param_1,byte param_2)

{
  undefined1 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  allocator<char> local_5;
  
  uVar2 = (uint)param_2;
  puVar3 = (undefined1 *)std::allocator<char>::allocator<char>(&local_5);
  uVar1 = FUN_007eab60(*puVar3,uVar2);
  *param_1 = uVar1;
  return param_1;
}

