
/* Library Function - Single Match
    public: void __thiscall std::tr1::_Ptr_base<class __ExceptionPtr>::_Reset0(class __ExceptionPtr
   *,class std::tr1::_Ref_count_base *)
   
   Library: Visual Studio 2010 Debug */

void __thiscall
std::tr1::_Ptr_base<class___ExceptionPtr>::_Reset0
          (_Ptr_base<class___ExceptionPtr> *this,__ExceptionPtr *param_1,_Ref_count_base *param_2)

{
  if (*(int *)(this + 4) != 0) {
    Decref();
  }
  *(_Ref_count_base **)(this + 4) = param_2;
  *(__ExceptionPtr **)this = param_1;
  return;
}

