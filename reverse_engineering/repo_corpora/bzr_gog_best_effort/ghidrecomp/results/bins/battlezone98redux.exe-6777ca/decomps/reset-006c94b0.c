
/* Library Function - Single Match
    public: void __thiscall std::shared_ptr<struct
   Concurrency::details::_ExceptionHolder>::reset(void)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall
std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
          (shared_ptr<struct_Concurrency::details::_ExceptionHolder> *this)

{
  shared_ptr<class___ExceptionPtr> *this_00;
  
  this_00 = (shared_ptr<class___ExceptionPtr> *)FUN_0068b0a0();
  shared_ptr<class___ExceptionPtr>::swap(this_00,(shared_ptr<class___ExceptionPtr> *)this);
  FUN_006ca8c0();
  return;
}

