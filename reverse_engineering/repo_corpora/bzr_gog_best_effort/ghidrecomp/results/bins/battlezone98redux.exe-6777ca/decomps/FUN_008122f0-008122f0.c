
char __thiscall FUN_008122f0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char cVar2;
  allocator<char> local_6;
  char local_5;
  
  std::allocator<char>::allocator<char>(&local_6);
  uVar1 = *(undefined4 *)*param_1;
  local_5 = FUN_00813070(param_2,&local_6);
  if (local_5 == '\0') {
    cVar2 = operator==<>(*(undefined1 *)param_1[4],local_6);
    local_5 = cVar2 == '\0';
    if ((bool)local_5) {
      *(undefined4 *)*param_1 = uVar1;
    }
  }
  return local_5;
}

