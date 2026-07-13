
undefined1 __thiscall
FUN_007ef480(allocator<char> *param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4,
            undefined1 *param_5)

{
  char cVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  uint uVar4;
  undefined1 local_c;
  allocator<char> local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  cVar1 = operator==<>(*param_5);
  if (cVar1 == '\0') {
    return 0;
  }
  local_5 = 0;
  puVar3 = &local_5;
  pbVar2 = (byte *)FUN_00417780(&local_7,*param_5,param_3,puVar3,param_3);
  uVar4 = (uint)*pbVar2;
  std::allocator<char>::allocator<char>(param_1);
  cVar1 = FUN_007efbd0(uVar4,puVar3,param_3);
  if (cVar1 != '\0') {
    local_6 = 0;
    puVar3 = (undefined1 *)std::allocator<char>::allocator<char>(&local_8);
    cVar1 = FUN_007efbf0(param_2,&local_5,local_6,*puVar3);
    if ((cVar1 == '\0') || (cVar1 = operator==<>(param_2,*param_4), cVar1 == '\0')) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
    return local_c;
  }
  return 0;
}

