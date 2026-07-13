/*
 * Entry: 005a03b0
 * Name: _vorbis_pack_info
 * Namespace: Global
 * Signature: int _vorbis_pack_info(oggpack_buffer * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_pack_info(oggpack_buffer *param_1,vorbis_info *param_2)

{
  int *piVar1;
  int in_EAX;
  uint uVar2;
  int iVar3;
  
  piVar1 = *(int **)(in_EAX + 0x1c);
  if (piVar1 != (int *)0x0) {
    oggpack_write();
    iVar3 = 6;
    do {
      iVar3 = iVar3 + -1;
      oggpack_write();
    } while (iVar3 != 0);
    oggpack_write();
    oggpack_write();
    oggpack_write();
    oggpack_write();
    oggpack_write();
    oggpack_write();
    if (*piVar1 != 0) {
      for (uVar2 = *piVar1 - 1; uVar2 != 0; uVar2 = uVar2 >> 1) {
      }
    }
    oggpack_write();
    if (piVar1[1] != 0) {
      for (uVar2 = piVar1[1] - 1; uVar2 != 0; uVar2 = uVar2 >> 1) {
      }
    }
    oggpack_write();
    oggpack_write();
    return 0;
  }
  return -0x81;
}
