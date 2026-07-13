
/* Library Function - Multiple Matches With Same Base Name
    private: bool __thiscall std::_Func_class<void,unsigned int const &,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>::_Local(void)const
   
    private: bool __thiscall std::_Func_class<void,unsigned char,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>::_Local(void)const
   
    private: bool __thiscall std::_Func_class<void,class Concurrency::message<unsigned int> *,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Local(void)const 
    private: bool __thiscall std::_Func_class<void,class Concurrency::message<enum
   Concurrency::agent_status> *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Local(void)const 
     9 names - too many to list
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

bool __fastcall Local(int param_1)

{
  return *(int *)(param_1 + 0x10) == param_1;
}

