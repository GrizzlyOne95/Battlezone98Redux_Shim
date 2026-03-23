
undefined1 __thiscall
FUN_007f1250(allocator<char> *param_1,undefined4 param_2,__ExceptionPtr *param_3,undefined1 *param_4
            ,shared_ptr<class___ExceptionPtr> *param_5)

{
  char cVar1;
  undefined4 extraout_EAX;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 local_c;
  allocator<char> local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  cVar1 = FUN_007ef400(param_5);
  if (cVar1 == '\0') {
    return 0;
  }
  local_5 = 0;
  puVar2 = &local_5;
  std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_5,param_3);
  uVar3 = extraout_EAX;
  std::allocator<char>::allocator<char>(param_1);
  cVar1 = FUN_007f1b70(uVar3,puVar2,param_3);
  if (cVar1 != '\0') {
    local_6 = 0;
    puVar2 = (undefined1 *)std::allocator<char>::allocator<char>(&local_7);
    cVar1 = FUN_007efbf0(param_2,&local_5,local_6,*puVar2);
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

