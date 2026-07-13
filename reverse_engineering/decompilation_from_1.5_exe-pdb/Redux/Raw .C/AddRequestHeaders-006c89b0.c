
/* Library Function - Multiple Matches With Same Base Name
    public: int __thiscall CHttpFile::AddRequestHeaders(class ATL::CStringT<char,class
   StrTraitMFC<char,class ATL::ChTraitsCRT<char> > > &,unsigned long)
    public: int __thiscall CHttpFile::AddRequestHeaders(class ATL::CStringT<wchar_t,class
   StrTraitMFC<wchar_t,class ATL::ChTraitsCRT<wchar_t> > > &,unsigned long)
    public: int __thiscall CHttpFile::AddRequestHeaders(class ATL::CStringT<wchar_t,class
   StrTraitMFC<wchar_t,class ATL::ChTraitsOS<wchar_t> > > &,unsigned long)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

void __thiscall
AddRequestHeaders(undefined4 param_1,_String_val<struct_std::_Simple_types<char>_> *param_2,
                 undefined4 param_3)

{
  undefined4 uVar1;
  char *pcVar2;
  
  uVar1 = FUN_004170c0(param_1);
  pcVar2 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr(param_2);
  FUN_005871e0(pcVar2,param_3,uVar1);
  return;
}

