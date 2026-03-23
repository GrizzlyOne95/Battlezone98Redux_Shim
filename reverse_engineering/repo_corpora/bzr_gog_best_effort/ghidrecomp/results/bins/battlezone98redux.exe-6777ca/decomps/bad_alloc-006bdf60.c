
/* Library Function - Single Match
    public: __thiscall std::bad_alloc::bad_alloc(class std::bad_alloc const &)
   
   Library: Visual Studio 2005 Debug */

bad_alloc * __thiscall std::bad_alloc::bad_alloc(bad_alloc *this,bad_alloc *param_1)

{
  std::exception::exception((exception *)this,(exception *)param_1);
  *(undefined ***)this = logic_error::vftable;
  return this;
}

