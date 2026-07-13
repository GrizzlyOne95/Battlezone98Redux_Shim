/*
 * Entry: 005a2a50
 * Name: vorbis_synthesis_trackonly
 * Namespace: Global
 * Signature: int vorbis_synthesis_trackonly(vorbis_block * param_1, ogg_packet * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_trackonly(vorbis_block *param_1,ogg_packet *param_2)

{
  oggpack_buffer *poVar1;
  void *pvVar2;
  void *pvVar3;
  int *piVar4;
  int iVar5;
  long lVar6;
  
  pvVar2 = param_1->vd->backend_state;
  pvVar3 = param_1->vd->vi->codec_setup;
  poVar1 = &param_1->opb;
  _vorbis_block_ripcord(param_1);
  oggpack_readinit(poVar1,param_2->packet,param_2->bytes);
  iVar5 = oggpack_read(poVar1,1);
  if (iVar5 != 0) {
    return -0x87;
  }
  iVar5 = oggpack_read(poVar1,*(undefined4 *)((int)pvVar2 + 0x2c));
  if (iVar5 != -1) {
    param_1->mode = iVar5;
    piVar4 = *(int **)((int)pvVar3 + iVar5 * 4 + 0x20);
    if (piVar4 != (int *)0x0) {
      iVar5 = *piVar4;
      param_1->W = iVar5;
      if (iVar5 == 0) {
        param_1->lW = 0;
        param_1->nW = 0;
      }
      else {
        lVar6 = oggpack_read(poVar1,1);
        param_1->lW = lVar6;
        iVar5 = oggpack_read(poVar1,1);
        param_1->nW = iVar5;
        if (iVar5 == -1) {
          return -0x88;
        }
      }
      *(int *)&param_1->granulepos = (int)param_2->granulepos;
      *(undefined4 *)((int)&param_1->granulepos + 4) =
           *(undefined4 *)((int)&param_2->granulepos + 4);
      *(int *)&param_1->sequence = (int)param_2->packetno;
      *(undefined4 *)((int)&param_1->sequence + 4) = *(undefined4 *)((int)&param_2->packetno + 4);
      iVar5 = param_2->e_o_s;
      param_1->pcmend = 0;
      param_1->pcm = (float **)0x0;
      param_1->eofflag = iVar5;
      return 0;
    }
  }
  return -0x88;
}
