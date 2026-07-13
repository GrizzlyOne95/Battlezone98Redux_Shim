
undefined1 __thiscall
FUN_007f1650(undefined4 param_1,undefined4 param_2,__ExceptionPtr *param_3,undefined4 param_4,
            shared_ptr<class___ExceptionPtr> *param_5)

{
  char cVar1;
  undefined8 *extraout_EAX;
  undefined1 local_8;
  
  cVar1 = FUN_007ef400(param_5,param_1);
  if (cVar1 != '\0') {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_5,param_3);
    cVar1 = FUN_007f2230(param_2,*extraout_EAX,param_1);
    if ((cVar1 == '\0') || (cVar1 = operator==<>(), cVar1 == '\0')) {
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
    return local_8;
  }
  return 0;
}

