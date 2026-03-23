
/* Library Function - Single Match
    public: struct IUnknown * __thiscall CWnd::GetControlUnknown(void)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

IUnknown * __thiscall CWnd::GetControlUnknown(CWnd *this)

{
  IUnknown *pIVar1;
  
  if (*(int *)(this + 0x54) == 0) {
    pIVar1 = (IUnknown *)0x0;
  }
  else {
    pIVar1 = *(IUnknown **)(*(int *)(this + 0x54) + 8);
  }
  return pIVar1;
}

