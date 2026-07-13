
/* Library Function - Single Match
    public: void __thiscall std::_Ref_count_base::_Incref(void)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall std::_Ref_count_base::_Incref(_Ref_count_base *this)

{
  LOCK();
  *(int *)(this + 4) = *(int *)(this + 4) + 1;
  UNLOCK();
  return;
}

