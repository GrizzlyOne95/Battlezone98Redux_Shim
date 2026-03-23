
bool __fastcall FUN_0080e850(undefined4 *param_1)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> local_5;
  
  cVar1 = FUN_0080fd40(*param_1,param_1[1],param_1[2],param_1[3],&local_5);
  if (cVar1 != '\0') {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              (&local_5,(__ExceptionPtr *)param_1[4]);
  }
  return cVar1 != '\0';
}

