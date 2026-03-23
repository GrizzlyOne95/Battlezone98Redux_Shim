
void __thiscall
FUN_006d9020(shared_ptr<class___ExceptionPtr> *param_1,undefined4 param_2,undefined1 param_3)

{
  shared_ptr<class___ExceptionPtr> *this;
  
  this = (shared_ptr<class___ExceptionPtr> *)FUN_006e7c40(param_2,param_3);
  std::shared_ptr<class___ExceptionPtr>::swap(this,param_1);
  FUN_006ca8c0();
  return;
}

