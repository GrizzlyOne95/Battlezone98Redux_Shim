
bool __fastcall FUN_0080c120(undefined4 *param_1)

{
  char cVar1;
  shared_ptr<class___ExceptionPtr> local_10 [8];
  undefined4 *local_8;
  
  local_8 = param_1;
  cVar1 = FUN_0080c9f0(*param_1,param_1[1],param_1[2],param_1[3],local_10);
  if (cVar1 != '\0') {
    std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
              (local_10,(__ExceptionPtr *)local_8[4]);
  }
  return cVar1 != '\0';
}

