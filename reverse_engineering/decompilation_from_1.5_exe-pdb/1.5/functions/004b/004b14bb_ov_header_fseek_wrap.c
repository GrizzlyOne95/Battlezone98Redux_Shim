/*
 * Entry: 004b14bb
 * Name: _ov_header_fseek_wrap
 * Namespace: Global
 * Signature: int _ov_header_fseek_wrap(_iobuf * param_1, long64 param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ov_header_fseek_wrap(_iobuf *param_1,long64 param_2,int param_3)

{
  int iVar1;
  int unaff_EBP;
  
  if (param_1 == (_iobuf *)0x0) {
    return -1;
  }
  iVar1 = _fseeki64((FILE *)param_1,param_2,unaff_EBP);
  return iVar1;
}
