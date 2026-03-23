
/* Library Function - Single Match
    public: virtual void __thiscall COleControlContainer::OnUIDeactivate(class COleControlSite *)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual Studio 2010 Debug */

void __thiscall
COleControlContainer::OnUIDeactivate(COleControlContainer *this,COleControlSite *param_1)

{
  if (*(COleControlSite **)(this + 0x14) == param_1) {
    *(undefined4 *)(this + 0x14) = 0;
  }
  if (*(COleControlSite **)(this + 0x18) == param_1) {
    *(undefined4 *)(this + 0x18) = 0;
  }
  return;
}

