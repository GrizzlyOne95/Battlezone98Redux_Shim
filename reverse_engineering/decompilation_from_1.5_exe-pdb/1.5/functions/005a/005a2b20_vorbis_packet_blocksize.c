/*
 * Entry: 005a2b20
 * Name: vorbis_packet_blocksize
 * Namespace: Global
 * Signature: long vorbis_packet_blocksize(vorbis_info * param_1, ogg_packet * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl vorbis_packet_blocksize(vorbis_info *param_1,ogg_packet *param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  undefined1 local_14 [20];
  
  pvVar1 = param_1->codec_setup;
  oggpack_readinit(local_14,param_2->packet,param_2->bytes);
  iVar2 = oggpack_read(local_14,1);
  if (iVar2 != 0) {
    return -0x87;
  }
  iVar3 = 0;
  for (iVar2 = *(int *)((int)pvVar1 + 8); 1 < iVar2; iVar2 = iVar2 >> 1) {
    iVar3 = iVar3 + 1;
  }
  iVar2 = oggpack_read(local_14,iVar3);
  if (iVar2 != -1) {
    return *(long *)((int)pvVar1 + **(int **)((int)pvVar1 + iVar2 * 4 + 0x20) * 4);
  }
  return -0x88;
}
