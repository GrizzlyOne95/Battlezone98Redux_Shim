
/* Library Function - Single Match
    public: __thiscall std::runtime_error::runtime_error(class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > const &)
   
   Libraries: Visual Studio 2019 Debug, Visual Studio 2019 Release */

runtime_error * __thiscall
std::runtime_error::runtime_error
          (runtime_error *this,
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0041f870();
  FUN_006ab5d0(uVar1);
  *(undefined ***)this = out_of_range::vftable;
  return this;
}

