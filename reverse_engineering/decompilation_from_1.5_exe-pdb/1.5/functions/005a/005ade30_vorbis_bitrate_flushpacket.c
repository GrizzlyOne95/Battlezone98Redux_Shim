/*
 * Entry: 005ade30
 * Name: vorbis_bitrate_flushpacket
 * Namespace: Global
 * Signature: int vorbis_bitrate_flushpacket(vorbis_dsp_state * param_1, ogg_packet * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_bitrate_flushpacket(vorbis_dsp_state *param_1,ogg_packet *param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uchar *puVar5;
  long lVar6;
  int iVar7;
  
  pvVar1 = param_1->backend_state;
  iVar2 = *(int *)((int)pvVar1 + 0x78);
  iVar7 = 7;
  if (iVar2 == 0) {
    return 0;
  }
  if (param_2 != (ogg_packet *)0x0) {
    piVar4 = (int *)(*(int *)(*(int *)(iVar2 + 0x40) + 0x68) + 0x50);
    iVar3 = *(int *)(iVar2 + 0x68);
    if ((piVar4 != (int *)0x0) && (*piVar4 != 0)) {
      iVar7 = *(int *)((int)pvVar1 + 0x7c);
    }
    puVar5 = (uchar *)oggpack_get_buffer(*(undefined4 *)(iVar3 + 0xc + iVar7 * 4));
    param_2->packet = puVar5;
    lVar6 = oggpack_bytes(*(undefined4 *)(iVar3 + 0xc + iVar7 * 4));
    param_2->bytes = lVar6;
    param_2->b_o_s = 0;
    param_2->e_o_s = *(long *)(iVar2 + 0x2c);
    *(undefined4 *)&param_2->granulepos = *(undefined4 *)(iVar2 + 0x30);
    *(undefined4 *)((int)&param_2->granulepos + 4) = *(undefined4 *)(iVar2 + 0x34);
    *(undefined4 *)&param_2->packetno = *(undefined4 *)(iVar2 + 0x38);
    *(undefined4 *)((int)&param_2->packetno + 4) = *(undefined4 *)(iVar2 + 0x3c);
  }
  *(undefined4 *)((int)pvVar1 + 0x78) = 0;
  return 1;
}
