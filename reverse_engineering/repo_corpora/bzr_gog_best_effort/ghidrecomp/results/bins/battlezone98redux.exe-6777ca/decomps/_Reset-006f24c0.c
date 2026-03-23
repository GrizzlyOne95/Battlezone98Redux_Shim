
/* Library Function - Single Match
    public: void __thiscall std::tr1::_Ptr_base<class __ExceptionPtr>::_Reset(class __ExceptionPtr
   *,class std::tr1::_Ref_count_base *,bool)
   
   Library: Visual Studio 2010 Debug */

void __thiscall
std::tr1::_Ptr_base<class___ExceptionPtr>::_Reset
          (_Ptr_base<class___ExceptionPtr> *this,__ExceptionPtr *param_1,_Ref_count_base *param_2,
          bool param_3)

{
  char cVar1;
  undefined1 local_14 [12];
  _Ptr_base<class___ExceptionPtr> *local_8;
  
  local_8 = this;
  if ((param_2 != (_Ref_count_base *)0x0) && (cVar1 = FUN_006ab490(), cVar1 != '\0')) {
    _Reset0(local_8,param_1,param_2);
    return;
  }
  if (!param_3) {
    return;
  }
  FUN_006ab3f0(0);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_14,(ThrowInfo *)&DAT_008d7fa8);
}

