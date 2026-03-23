
void __thiscall FUN_0070fb90(shared_ptr<class___ExceptionPtr> *param_1,undefined4 param_2)

{
  shared_ptr<class___ExceptionPtr> *this;
  
  this = (shared_ptr<class___ExceptionPtr> *)FUN_0071ac60(param_2);
  std::shared_ptr<class___ExceptionPtr>::swap(this,param_1);
  FUN_006ca8c0();
  return;
}

