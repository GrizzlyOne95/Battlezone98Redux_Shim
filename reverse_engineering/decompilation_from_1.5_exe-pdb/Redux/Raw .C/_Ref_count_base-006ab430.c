
/* Library Function - Single Match
    protected: __thiscall std::_Ref_count_base::_Ref_count_base(void)
   
   Library: Visual Studio 2012 Debug */

_Ref_count_base * __thiscall std::_Ref_count_base::_Ref_count_base(_Ref_count_base *this)

{
  *(undefined ***)this = vftable;
  _Init_atomic_counter((ulong *)(this + 4),1);
  _Init_atomic_counter((ulong *)(this + 8),1);
  return this;
}

