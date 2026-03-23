
/* Library Function - Single Match
    public: void __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::reserve(unsigned int)
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1)

{
  undefined4 uVar1;
  char cVar2;
  
  if ((*(uint *)(this + 0x10) <= param_1) && (*(uint *)(this + 0x14) != param_1)) {
    uVar1 = *(undefined4 *)(this + 0x10);
    cVar2 = FID_conflict__Grow(param_1,1);
    if (cVar2 != '\0') {
      FID_conflict__Eos(uVar1);
    }
  }
  return;
}

