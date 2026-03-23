
/* Library Function - Single Match
    public: class std::_String_const_iterator<class std::_String_val<struct std::_Simple_types<char>
   > > & __thiscall std::_String_const_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >::operator++(void)
   
   Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release */

_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> * __thiscall
std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::operator++
          (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *this)

{
  *(int *)this = *(int *)this + 1;
  return this;
}

