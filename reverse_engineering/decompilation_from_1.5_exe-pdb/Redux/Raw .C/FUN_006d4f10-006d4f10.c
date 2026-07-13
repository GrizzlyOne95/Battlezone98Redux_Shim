
shared_ptr<class___ExceptionPtr> * __thiscall
FUN_006d4f10(shared_ptr<class___ExceptionPtr> *param_1,shared_ptr<class___ExceptionPtr> *param_2)

{
  std::shared_ptr<class___ExceptionPtr>::operator=(param_1,param_2);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
  return param_1;
}

