
undefined1 __thiscall
FUN_007edae0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4)

{
  char cVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  uint uVar4;
  allocator<char> local_6;
  allocator<char> local_5;
  
  pbVar2 = (byte *)std::allocator<char>::allocator<char>(&local_5);
  uVar4 = (uint)*pbVar2;
  puVar3 = (undefined1 *)std::allocator<char>::allocator<char>(&local_6);
  cVar1 = FUN_007ee7f0(param_2,param_1,*puVar3,uVar4);
  if ((cVar1 != '\0') && (cVar1 = operator==<>(param_2,*param_4), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

