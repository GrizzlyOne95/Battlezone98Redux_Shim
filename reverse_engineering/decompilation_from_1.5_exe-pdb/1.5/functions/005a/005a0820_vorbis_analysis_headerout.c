/*
 * Entry: 005a0820
 * Name: vorbis_analysis_headerout
 * Namespace: Global
 * Signature: int vorbis_analysis_headerout(vorbis_dsp_state * param_1, vorbis_comment * param_2, ogg_packet * param_3, ogg_packet * param_4, ogg_packet * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
vorbis_analysis_headerout
          (vorbis_dsp_state *param_1,vorbis_comment *param_2,ogg_packet *param_3,ogg_packet *param_4
          ,ogg_packet *param_5)

{
  void *pvVar1;
  vorbis_info *pvVar2;
  int iVar3;
  size_t sVar4;
  void *pvVar5;
  undefined4 uVar6;
  long lVar7;
  vorbis_info *unaff_ESI;
  oggpack_buffer *unaff_EDI;
  vorbis_comment *pvVar8;
  vorbis_info *pvVar9;
  int local_18;
  vorbis_comment local_14;
  
  pvVar1 = param_1->backend_state;
  pvVar2 = param_1->vi;
  local_18 = -0x82;
  if (pvVar1 == (void *)0x0) {
    local_18 = -0x81;
  }
  else {
    oggpack_writeinit(&local_14);
    iVar3 = _vorbis_pack_info(unaff_EDI,unaff_ESI);
    if (iVar3 == 0) {
      if (*(void **)((int)pvVar1 + 0x40) != (void *)0x0) {
        free(*(void **)((int)pvVar1 + 0x40));
      }
      sVar4 = oggpack_bytes(&local_14);
      pvVar5 = malloc(sVar4);
      *(void **)((int)pvVar1 + 0x40) = pvVar5;
      uVar6 = oggpack_bytes(&local_14);
      memcpy(*(undefined4 *)((int)pvVar1 + 0x40),local_14.comments,uVar6);
      param_3->packet = *(uchar **)((int)pvVar1 + 0x40);
      lVar7 = oggpack_bytes(&local_14);
      pvVar8 = &local_14;
      param_3->bytes = lVar7;
      param_3->b_o_s = 1;
      param_3->e_o_s = 0;
      *(undefined4 *)&param_3->granulepos = 0;
      *(undefined4 *)((int)&param_3->granulepos + 4) = 0;
      *(undefined4 *)&param_3->packetno = 0;
      *(undefined4 *)((int)&param_3->packetno + 4) = 0;
      oggpack_reset();
      iVar3 = _vorbis_pack_comment((oggpack_buffer *)param_2,pvVar8);
      if (iVar3 == 0) {
        if (*(void **)((int)pvVar1 + 0x44) != (void *)0x0) {
          free(*(void **)((int)pvVar1 + 0x44));
        }
        sVar4 = oggpack_bytes(&local_14);
        pvVar5 = malloc(sVar4);
        *(void **)((int)pvVar1 + 0x44) = pvVar5;
        uVar6 = oggpack_bytes(&local_14);
        memcpy(*(undefined4 *)((int)pvVar1 + 0x44),local_14.comments,uVar6);
        param_4->packet = *(uchar **)((int)pvVar1 + 0x44);
        lVar7 = oggpack_bytes(&local_14);
        param_4->bytes = lVar7;
        pvVar9 = (vorbis_info *)&local_14;
        param_4->b_o_s = 0;
        param_4->e_o_s = 0;
        *(undefined4 *)&param_4->granulepos = 0;
        *(undefined4 *)((int)&param_4->granulepos + 4) = 0;
        *(undefined4 *)&param_4->packetno = 1;
        *(undefined4 *)((int)&param_4->packetno + 4) = 0;
        oggpack_reset();
        iVar3 = _vorbis_pack_books((oggpack_buffer *)pvVar2,pvVar9);
        if (iVar3 == 0) {
          if (*(void **)((int)pvVar1 + 0x48) != (void *)0x0) {
            free(*(void **)((int)pvVar1 + 0x48));
          }
          sVar4 = oggpack_bytes(&local_14);
          pvVar5 = malloc(sVar4);
          *(void **)((int)pvVar1 + 0x48) = pvVar5;
          uVar6 = oggpack_bytes(&local_14);
          memcpy(*(undefined4 *)((int)pvVar1 + 0x48),local_14.comments,uVar6);
          param_5->packet = *(uchar **)((int)pvVar1 + 0x48);
          lVar7 = oggpack_bytes(&local_14);
          param_5->bytes = lVar7;
          param_5->b_o_s = 0;
          param_5->e_o_s = 0;
          *(undefined4 *)&param_5->granulepos = 0;
          *(undefined4 *)((int)&param_5->granulepos + 4) = 0;
          *(undefined4 *)&param_5->packetno = 2;
          *(undefined4 *)((int)&param_5->packetno + 4) = 0;
          oggpack_writeclear(&local_14);
          return 0;
        }
      }
    }
  }
  param_3->packet = (uchar *)0x0;
  param_3->bytes = 0;
  param_3->b_o_s = 0;
  param_3->e_o_s = 0;
  *(undefined4 *)&param_3->granulepos = 0;
  *(undefined4 *)((int)&param_3->granulepos + 4) = 0;
  *(undefined4 *)&param_3->packetno = 0;
  *(undefined4 *)((int)&param_3->packetno + 4) = 0;
  param_4->packet = (uchar *)0x0;
  param_4->bytes = 0;
  param_4->b_o_s = 0;
  param_4->e_o_s = 0;
  *(undefined4 *)&param_4->granulepos = 0;
  *(undefined4 *)((int)&param_4->granulepos + 4) = 0;
  *(undefined4 *)&param_4->packetno = 0;
  *(undefined4 *)((int)&param_4->packetno + 4) = 0;
  param_5->packet = (uchar *)0x0;
  param_5->bytes = 0;
  param_5->b_o_s = 0;
  param_5->e_o_s = 0;
  *(undefined4 *)&param_5->granulepos = 0;
  *(undefined4 *)((int)&param_5->granulepos + 4) = 0;
  *(undefined4 *)&param_5->packetno = 0;
  *(undefined4 *)((int)&param_5->packetno + 4) = 0;
  if (pvVar1 != (void *)0x0) {
    oggpack_writeclear(&local_14);
    if (*(void **)((int)pvVar1 + 0x40) != (void *)0x0) {
      free(*(void **)((int)pvVar1 + 0x40));
    }
    if (*(void **)((int)pvVar1 + 0x44) != (void *)0x0) {
      free(*(void **)((int)pvVar1 + 0x44));
    }
    if (*(void **)((int)pvVar1 + 0x48) != (void *)0x0) {
      free(*(void **)((int)pvVar1 + 0x48));
    }
    *(undefined4 *)((int)pvVar1 + 0x40) = 0;
    *(undefined4 *)((int)pvVar1 + 0x44) = 0;
    *(undefined4 *)((int)pvVar1 + 0x48) = 0;
  }
  return local_18;
}
