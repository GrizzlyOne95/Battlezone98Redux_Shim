/*
 * Entry: 005a28b0
 * Name: vorbis_synthesis
 * Namespace: Global
 * Signature: int vorbis_synthesis(vorbis_block * param_1, ogg_packet * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis(vorbis_block *param_1,ogg_packet *param_2)

{
  int *piVar1;
  vorbis_block *pvVar2;
  vorbis_dsp_state *pvVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  float **ppfVar7;
  float *pfVar8;
  void *pvVar9;
  oggpack_buffer *poVar10;
  vorbis_info *local_4;
  
  pvVar2 = param_1;
  if (param_1 == (vorbis_block *)0x0) {
    pvVar3 = (vorbis_dsp_state *)0x0;
LAB_005a28de:
    param_1 = (vorbis_block *)0x0;
    local_4 = (vorbis_info *)0x0;
  }
  else {
    pvVar3 = param_1->vd;
    if (pvVar3 == (vorbis_dsp_state *)0x0) goto LAB_005a28de;
    param_1 = pvVar3->backend_state;
    local_4 = pvVar3->vi;
    if (local_4 != (vorbis_info *)0x0) {
      pvVar9 = local_4->codec_setup;
      goto LAB_005a28ea;
    }
  }
  pvVar9 = (void *)0x0;
LAB_005a28ea:
  if (pvVar2 == (vorbis_block *)0x0) {
    poVar10 = (oggpack_buffer *)0x0;
  }
  else {
    poVar10 = &pvVar2->opb;
  }
  if ((((pvVar3 != (vorbis_dsp_state *)0x0) && (param_1 != (vorbis_block *)0x0)) &&
      (local_4 != (vorbis_info *)0x0)) &&
     ((pvVar9 != (void *)0x0 && (poVar10 != (oggpack_buffer *)0x0)))) {
    _vorbis_block_ripcord(pvVar2);
    oggpack_readinit(poVar10,param_2->packet,param_2->bytes);
    iVar4 = oggpack_read(poVar10,1);
    if (iVar4 != 0) {
      return -0x87;
    }
    iVar4 = oggpack_read(poVar10,param_1->eofflag);
    if (iVar4 != -1) {
      pvVar2->mode = iVar4;
      piVar1 = *(int **)((int)pvVar9 + iVar4 * 4 + 0x20);
      if (piVar1 != (int *)0x0) {
        iVar6 = *piVar1;
        pvVar2->W = iVar6;
        if (iVar6 == 0) {
          pvVar2->lW = 0;
          pvVar2->nW = 0;
        }
        else {
          lVar5 = oggpack_read(poVar10,1);
          pvVar2->lW = lVar5;
          iVar6 = oggpack_read(poVar10,1);
          pvVar2->nW = iVar6;
          if (iVar6 == -1) {
            return -0x88;
          }
        }
        *(int *)&pvVar2->granulepos = (int)param_2->granulepos;
        *(undefined4 *)((int)&pvVar2->granulepos + 4) =
             *(undefined4 *)((int)&param_2->granulepos + 4);
        *(int *)&pvVar2->sequence = (int)param_2->packetno;
        iVar6 = pvVar2->W;
        *(undefined4 *)((int)&pvVar2->sequence + 4) = *(undefined4 *)((int)&param_2->packetno + 4);
        pvVar2->eofflag = param_2->e_o_s;
        pvVar2->pcmend = *(int *)((int)pvVar9 + iVar6 * 4);
        ppfVar7 = _vorbis_block_alloc(pvVar2,local_4->channels * 4);
        iVar6 = 0;
        pvVar2->pcm = ppfVar7;
        if (0 < local_4->channels) {
          do {
            pfVar8 = _vorbis_block_alloc(pvVar2,pvVar2->pcmend * 4);
            pvVar2->pcm[iVar6] = pfVar8;
            iVar6 = iVar6 + 1;
          } while (iVar6 < local_4->channels);
        }
        iVar4 = *(int *)(*(int *)((int)pvVar9 + iVar4 * 4 + 0x20) + 0xc);
        iVar4 = (**(code **)(*(int *)(&_mapping_P + *(int *)((int)pvVar9 + iVar4 * 4 + 0x120) * 4) +
                            0x10))(pvVar2,*(undefined4 *)((int)pvVar9 + iVar4 * 4 + 0x220));
        return iVar4;
      }
    }
    return -0x88;
  }
  return -0x88;
}
