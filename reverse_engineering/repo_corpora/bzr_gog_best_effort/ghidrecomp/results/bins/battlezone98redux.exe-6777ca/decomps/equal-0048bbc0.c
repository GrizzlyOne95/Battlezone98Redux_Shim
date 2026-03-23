
/* Library Function - Multiple Matches With Same Base Name
    public: bool __thiscall std::istreambuf_iterator<char,struct std::char_traits<char>
   >::equal(class std::istreambuf_iterator<char,struct std::char_traits<char> > const &)const 
    public: bool __thiscall std::istreambuf_iterator<unsigned short,struct std::char_traits<unsigned
   short> >::equal(class std::istreambuf_iterator<unsigned short,struct std::char_traits<unsigned
   short> > const &)const 
    public: bool __thiscall std::istreambuf_iterator<wchar_t,struct std::char_traits<wchar_t>
   >::equal(class std::istreambuf_iterator<wchar_t,struct std::char_traits<wchar_t> > const &)const 
   
   Library: Visual Studio */

undefined1 __thiscall equal(int *param_1,int *param_2)

{
  undefined1 local_c;
  
  if ((char)param_1[1] == '\0') {
    FUN_0048ac50();
  }
  if ((char)param_2[1] == '\0') {
    FUN_0048ac50();
  }
  if (((*param_1 == 0) && (*param_2 == 0)) || ((*param_1 != 0 && (*param_2 != 0)))) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}

