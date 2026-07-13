/*
 * Entry: 0059be40
 * Name: _fseek64_wrap
 * Namespace: Global
 * Signature: int _fseek64_wrap(_iobuf * param_1, long64 param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _fseek64_wrap(_iobuf *param_1,long64 param_2,int param_3)

{
  int iVar1;
  long in_stack_00000008;
  
  if (param_1 == (_iobuf *)0x0) {
    iVar1 = -1;
  }
  else {
    iVar1 = fseek((FILE *)param_1,in_stack_00000008,param_2._4_4_);
  }
  return iVar1;
}
