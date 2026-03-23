
/* Library Function - Single Match
    public: __thiscall COleCurrency::operator union tagCY(void)const 
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

undefined4 * __thiscall COleCurrency::operator_union_tagCY(COleCurrency *this)

{
  undefined4 uVar1;
  undefined4 *in_stack_00000004;
  
  uVar1 = *(undefined4 *)(this + 4);
  *in_stack_00000004 = *(undefined4 *)this;
  in_stack_00000004[1] = uVar1;
  return in_stack_00000004;
}

