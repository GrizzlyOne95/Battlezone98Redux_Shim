/*
 * Entry: 005a0490
 * Name: _vorbis_pack_comment
 * Namespace: Global
 * Signature: int _vorbis_pack_comment(oggpack_buffer * param_1, vorbis_comment * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_pack_comment(oggpack_buffer *param_1,vorbis_comment *param_2)

{
  int iVar1;
  int iVar2;
  
  oggpack_write();
  iVar1 = 6;
  do {
    iVar1 = iVar1 + -1;
    oggpack_write();
  } while (iVar1 != 0);
  oggpack_write();
  iVar1 = 0x2f;
  do {
    iVar1 = iVar1 + -1;
    oggpack_write();
  } while (iVar1 != 0);
  oggpack_write();
  if ((param_1->buffer != (uchar *)0x0) && (iVar1 = 0, 0 < (int)param_1->buffer)) {
    do {
      if (*(int *)(param_1->endbyte + iVar1 * 4) == 0) {
        oggpack_write();
      }
      else {
        oggpack_write();
        for (iVar2 = *(int *)(param_1->endbit + iVar1 * 4); iVar2 != 0; iVar2 = iVar2 + -1) {
          oggpack_write();
        }
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)param_1->buffer);
  }
  oggpack_write();
  return 0;
}
