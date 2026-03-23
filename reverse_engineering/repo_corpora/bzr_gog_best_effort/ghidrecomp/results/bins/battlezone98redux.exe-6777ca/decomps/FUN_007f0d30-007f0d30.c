
undefined1 __thiscall
FUN_007f0d30(undefined4 param_1,undefined4 param_2,__ExceptionPtr *param_3,undefined1 *param_4,
            shared_ptr<class___ExceptionPtr> *param_5)

{
  char cVar1;
  undefined4 extraout_EAX;
  
  cVar1 = FUN_007ef400(param_5,param_1);
  if (cVar1 == '\0') {
    return 0;
  }
  std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_5,param_3);
  cVar1 = FUN_007f15d0(param_2,extraout_EAX);
  if ((cVar1 != '\0') && (cVar1 = operator==<>(param_2,*param_4), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

