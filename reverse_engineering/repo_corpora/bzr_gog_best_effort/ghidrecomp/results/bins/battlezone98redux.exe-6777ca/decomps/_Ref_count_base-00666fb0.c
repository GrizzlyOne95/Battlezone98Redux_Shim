
/* Library Function - Single Match
    protected: __thiscall std::tr1::_Ref_count_base::_Ref_count_base(void)
   
   Library: Visual Studio 2010 Debug */

_Ref_count_base * __thiscall std::tr1::_Ref_count_base::_Ref_count_base(_Ref_count_base *this)

{
  *(undefined ***)this = boost::detail::sp_counted_base::vftable;
  *(undefined4 *)(this + 4) = 1;
  *(undefined4 *)(this + 8) = 1;
  return this;
}

