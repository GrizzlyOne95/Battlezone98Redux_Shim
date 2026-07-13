
/* Library Function - Multiple Matches With Same Base Name
    protected: void __thiscall std::_Func_class<void,class Concurrency::message<unsigned int>
   *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Reset(class std::_Func_class<void,class Concurrency::message<unsigned int> *,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>
   const &)
    protected: void __thiscall std::_Func_class<void,class Concurrency::message<enum
   Concurrency::agent_status> *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Reset(class std::_Func_class<void,class
   Concurrency::message<enum Concurrency::agent_status> *,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil> const &)
    protected: void __thiscall std::_Func_class<void,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>::_Reset(class
   std::_Func_class<void,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil> const &)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall Reset(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_2 + 0x10) == 0) {
    Set(0);
  }
  else {
    cVar1 = Local(param_1);
    if (cVar1 == '\0') {
      uVar2 = (**(code **)**(undefined4 **)(param_2 + 0x10))(0);
      Set(uVar2);
    }
    else {
      uVar2 = (**(code **)**(undefined4 **)(param_2 + 0x10))(param_1);
      Set(uVar2);
    }
  }
  return;
}

