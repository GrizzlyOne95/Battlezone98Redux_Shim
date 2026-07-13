
/* Library Function - Single Match
    public: __thiscall std::_Iterator_base12::_Iterator_base12(struct std::_Iterator_base12 const &)
   
   Library: Visual Studio 2015 Release */

_Iterator_base12 * __thiscall
std::_Iterator_base12::_Iterator_base12(_Iterator_base12 *this,_Iterator_base12 *param_1)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 4) = 0;
  operator=(this,param_1);
  return this;
}

