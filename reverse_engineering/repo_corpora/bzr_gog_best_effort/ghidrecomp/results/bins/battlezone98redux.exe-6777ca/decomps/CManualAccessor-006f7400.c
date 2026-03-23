
/* Library Function - Single Match
    public: __thiscall ATL::CManualAccessor::CManualAccessor(void)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

CManualAccessor * __thiscall ATL::CManualAccessor::CManualAccessor(CManualAccessor *this)

{
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)this);
  *(undefined4 *)(this + 8) = 0;
  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x14) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  return this;
}

