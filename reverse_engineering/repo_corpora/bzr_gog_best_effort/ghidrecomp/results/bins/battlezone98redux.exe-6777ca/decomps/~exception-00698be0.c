
/* Library Function - Single Match
    public: virtual __thiscall exception::~exception(void)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __thiscall exception::~exception(exception *this)

{
  *(undefined ***)this = Goal::vftable;
  if (*(int *)(this + 0x14) != 0) {
    FUN_006a89e0(*(undefined4 *)(this + 0x14));
  }
  return;
}

