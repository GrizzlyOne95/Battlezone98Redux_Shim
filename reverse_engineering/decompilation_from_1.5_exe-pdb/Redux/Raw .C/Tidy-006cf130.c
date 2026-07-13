
/* Library Function - Multiple Matches With Same Base Name
    protected: void __thiscall std::_Func_class<void,class Concurrency::message<unsigned int>
   *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Tidy(void)
    protected: void __thiscall std::_Func_class<void,class Concurrency::message<enum
   Concurrency::agent_status> *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Tidy(void)
    protected: void __thiscall std::_Func_class<void,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>::_Tidy(void)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __fastcall Tidy(int param_1)

{
  char cVar1;
  
  if (*(int *)(param_1 + 0x10) != 0) {
    cVar1 = Local();
    (**(code **)(**(int **)(param_1 + 0x10) + 0x10))(cVar1 == '\0');
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return;
}

