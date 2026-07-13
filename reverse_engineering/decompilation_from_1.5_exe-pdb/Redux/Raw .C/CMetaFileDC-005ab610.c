
/* Library Function - Single Match
    public: __thiscall CMetaFileDC::CMetaFileDC(void)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

CMetaFileDC * __thiscall CMetaFileDC::CMetaFileDC(CMetaFileDC *this)

{
  CDC::CDC((CDC *)this);
  *(undefined ***)this = PowerUpProcess::vftable;
  return this;
}

