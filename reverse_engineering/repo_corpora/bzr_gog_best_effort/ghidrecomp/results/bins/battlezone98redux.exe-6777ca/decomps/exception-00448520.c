
/* Library Function - Single Match
    protected: __thiscall boost::exception::exception(void)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

exception * __thiscall boost::exception::exception(exception *this)

{
  *(undefined ***)this = vftable;
  FUN_00423890();
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x10) = 0xffffffff;
  return this;
}

