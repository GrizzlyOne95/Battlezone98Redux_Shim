
/* Library Function - Single Match
    public: void __thiscall std::_Iterator_base12::_Adopt(struct std::_Container_base12 const *)
   
   Library: Visual Studio 2015 Release */

void __thiscall std::_Iterator_base12::_Adopt(_Iterator_base12 *this,_Container_base12 *param_1)

{
  if (param_1 != (_Container_base12 *)0x0) {
    *(undefined4 *)this = *(undefined4 *)param_1;
  }
  return;
}

