
/* Library Function - Single Match
    public: class std::shared_ptr<class __ExceptionPtr> & __thiscall std::shared_ptr<class
   __ExceptionPtr>::operator=(class std::shared_ptr<class __ExceptionPtr> const &)
   
   Library: Visual Studio 2012 Debug */

shared_ptr<class___ExceptionPtr> * __thiscall
std::shared_ptr<class___ExceptionPtr>::operator=
          (shared_ptr<class___ExceptionPtr> *this,shared_ptr<class___ExceptionPtr> *param_1)

{
  shared_ptr<class___ExceptionPtr> *this_00;
  shared_ptr<class___ExceptionPtr> local_10 [8];
  shared_ptr<class___ExceptionPtr> *local_8;
  
  local_8 = this;
  this_00 = (shared_ptr<class___ExceptionPtr> *)shared_ptr<class___ExceptionPtr>(local_10,param_1);
  swap(this_00,this);
  FUN_006ca8c0();
  return local_8;
}

