
/* Library Function - Multiple Matches With Same Base Name
    public: static unsigned short * __cdecl std::char_traits<unsigned short>::assign(unsigned short
   *,unsigned int,unsigned short)
    public: static wchar_t * __cdecl std::char_traits<wchar_t>::assign(wchar_t *,unsigned
   int,wchar_t)
   
   Libraries: Visual Studio 2008, Visual Studio 2010, Visual Studio 2012, Visual Studio 2015 */

void assign(wchar_t *param_1,size_t param_2,wchar_t param_3)

{
  _wmemset(param_1,param_3,param_2);
  return;
}

