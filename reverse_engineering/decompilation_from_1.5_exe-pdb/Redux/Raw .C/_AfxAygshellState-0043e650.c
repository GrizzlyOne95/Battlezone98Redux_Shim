
/* Library Function - Single Match
    struct _AFX_AYGSHELL_STATE & __cdecl _AfxAygshellState(void)
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug */

_AFX_AYGSHELL_STATE * __cdecl _AfxAygshellState(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00845f9e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((DAT_02cc2e10 & 1) == 0) {
    DAT_02cc2e10 = DAT_02cc2e10 | 1;
    local_8 = 0;
    FUN_0043e550(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_0083e979(FUN_00866110);
  }
  ExceptionList = local_10;
  return (_AFX_AYGSHELL_STATE *)&DAT_02cc2e0c;
}

