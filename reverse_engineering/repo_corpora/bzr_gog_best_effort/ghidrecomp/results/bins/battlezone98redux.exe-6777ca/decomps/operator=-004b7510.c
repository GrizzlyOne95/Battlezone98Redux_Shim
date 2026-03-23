
/* Library Function - Single Match
    public: struct std::_Iterator_base12 & __thiscall std::_Iterator_base12::operator=(struct
   std::_Iterator_base12 const &)
   
   Library: Visual Studio 2015 Release */

_Iterator_base12 * __thiscall
std::_Iterator_base12::operator=(_Iterator_base12 *this,_Iterator_base12 *param_1)

{
  if ((*(int *)this != *(int *)param_1) && (*(int *)param_1 != 0)) {
    _Adopt(this,(_Container_base12 *)**(undefined4 **)param_1);
  }
  return this;
}

