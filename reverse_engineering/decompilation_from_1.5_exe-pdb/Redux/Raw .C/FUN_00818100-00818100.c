
bool FUN_00818100(undefined4 param_1,undefined4 param_2,__ExceptionPtr *param_3)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> local_8 [4];
  
  cVar1 = FUN_00818140(param_1,param_2,local_8);
  if (cVar1 != '\0') {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(local_8,param_3);
  }
  return cVar1 != '\0';
}

