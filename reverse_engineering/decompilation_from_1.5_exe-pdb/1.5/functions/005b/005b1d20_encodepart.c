/*
 * Entry: 005b1d20
 * Name: _encodepart
 * Namespace: Global
 * Signature: int _encodepart(oggpack_buffer * param_1, int * param_2, int param_3, codebook * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _encodepart(oggpack_buffer *param_1,int *param_2,int param_3,codebook *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_4;
  
  iVar1 = param_4->dim;
  iVar2 = param_3 / iVar1;
  local_4 = 0;
  if (iVar2 < 1) {
    return 0;
  }
  do {
    iVar3 = local_book_besterror(param_4,param_2);
    iVar3 = vorbis_book_encode(param_4,iVar3,param_1);
    local_4 = local_4 + iVar3;
    param_2 = param_2 + iVar1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return local_4;
}
