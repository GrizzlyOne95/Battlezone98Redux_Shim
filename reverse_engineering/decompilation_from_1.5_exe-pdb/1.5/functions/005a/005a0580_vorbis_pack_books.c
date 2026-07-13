/*
 * Entry: 005a0580
 * Name: _vorbis_pack_books
 * Namespace: Global
 * Signature: int _vorbis_pack_books(oggpack_buffer * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_pack_books(oggpack_buffer *param_1,vorbis_info *param_2)

{
  uchar *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uchar *puVar5;
  oggpack_buffer *unaff_ESI;
  
  puVar1 = param_1[1].buffer;
  if (puVar1 == (uchar *)0x0) {
    return -0x81;
  }
  oggpack_write();
  iVar3 = 6;
  do {
    iVar3 = iVar3 + -1;
    oggpack_write();
  } while (iVar3 != 0);
  oggpack_write();
  if (0 < *(int *)(puVar1 + 0x18)) {
    puVar5 = puVar1 + 0x720;
    iVar3 = 0;
    do {
      iVar2 = vorbis_staticbook_pack(*(static_codebook **)puVar5,unaff_ESI);
      if (iVar2 != 0) {
        return -1;
      }
      iVar3 = iVar3 + 1;
      puVar5 = puVar5 + 4;
    } while (iVar3 < *(int *)(puVar1 + 0x18));
  }
  oggpack_write();
  oggpack_write();
  oggpack_write();
  iVar3 = 0;
  if (0 < *(int *)(puVar1 + 0x10)) {
    piVar4 = (int *)(puVar1 + 800);
    do {
      oggpack_write();
      if (**(int **)(&_floor_P + *piVar4 * 4) == 0) {
        return -1;
      }
      (*(code *)**(int **)(&_floor_P + *piVar4 * 4))(piVar4[0x40]);
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < *(int *)(puVar1 + 0x10));
  }
  oggpack_write();
  iVar3 = 0;
  if (0 < *(int *)(puVar1 + 0x14)) {
    piVar4 = (int *)(puVar1 + 0x520);
    do {
      oggpack_write();
      (*(code *)**(undefined4 **)(&_residue_P + *piVar4 * 4))(piVar4[0x40]);
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < *(int *)(puVar1 + 0x14));
  }
  oggpack_write();
  iVar3 = 0;
  if (0 < *(int *)(puVar1 + 0xc)) {
    piVar4 = (int *)(puVar1 + 0x120);
    do {
      oggpack_write();
      (*(code *)**(undefined4 **)(&_mapping_P + *piVar4 * 4))(param_1,piVar4[0x40]);
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < *(int *)(puVar1 + 0xc));
  }
  oggpack_write();
  iVar3 = 0;
  if (0 < *(int *)(puVar1 + 8)) {
    do {
      oggpack_write();
      oggpack_write();
      oggpack_write();
      oggpack_write();
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(puVar1 + 8));
  }
  oggpack_write();
  return 0;
}
