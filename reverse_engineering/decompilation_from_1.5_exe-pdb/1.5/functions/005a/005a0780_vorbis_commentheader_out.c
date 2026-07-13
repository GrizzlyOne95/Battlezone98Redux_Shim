/*
 * Entry: 005a0780
 * Name: vorbis_commentheader_out
 * Namespace: Global
 * Signature: int vorbis_commentheader_out(vorbis_comment * param_1, ogg_packet * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_commentheader_out(vorbis_comment *param_1,ogg_packet *param_2)

{
  int iVar1;
  size_t _Size;
  uchar *puVar2;
  undefined4 uVar3;
  long lVar4;
  vorbis_comment *pvVar5;
  vorbis_comment local_14;
  
  pvVar5 = &local_14;
  oggpack_writeinit();
  iVar1 = _vorbis_pack_comment((oggpack_buffer *)param_1,pvVar5);
  if (iVar1 != 0) {
    oggpack_writeclear(&local_14);
    return -0x82;
  }
  _Size = oggpack_bytes(&local_14);
  puVar2 = malloc(_Size);
  param_2->packet = puVar2;
  uVar3 = oggpack_bytes(&local_14);
  memcpy(param_2->packet,local_14.comments,uVar3);
  lVar4 = oggpack_bytes(&local_14);
  param_2->bytes = lVar4;
  param_2->b_o_s = 0;
  param_2->e_o_s = 0;
  *(undefined4 *)&param_2->granulepos = 0;
  *(undefined4 *)((int)&param_2->granulepos + 4) = 0;
  *(undefined4 *)&param_2->packetno = 1;
  *(undefined4 *)((int)&param_2->packetno + 4) = 0;
  oggpack_writeclear(&local_14);
  return 0;
}
