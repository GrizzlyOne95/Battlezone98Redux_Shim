/*
 * Entry: 0059ec90
 * Name: ov_read_float
 * Namespace: Global
 * Signature: long ov_read_float(OggVorbis_File * param_1, float * * * param_2, int param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ov_read_float(OggVorbis_File *param_1,float ***param_2,int param_3,int *param_4)

{
  long64 lVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  int local_c;
  float **local_8;
  
  if (param_1->ready_state < 2) {
    lVar2 = -0x83;
  }
  else {
    do {
      if ((param_1->ready_state == 4) &&
         (local_c = vorbis_synthesis_pcmout(&param_1->vd,&local_8), local_c != 0)) {
        iVar3 = vorbis_synthesis_halfrate_p(param_1->vi);
        if (param_2 != (float ***)0x0) {
          *param_2 = local_8;
        }
        if (param_3 < local_c) {
          local_c = param_3;
        }
        vorbis_synthesis_read(&param_1->vd,local_c);
        uVar4 = local_c << ((byte)iVar3 & 0x1f);
        lVar1 = param_1->pcm_offset;
        iVar3 = *(int *)((int)&param_1->pcm_offset + 4);
        *(uint *)&param_1->pcm_offset = uVar4 + (int)param_1->pcm_offset;
        *(uint *)((int)&param_1->pcm_offset + 4) =
             iVar3 + ((int)uVar4 >> 0x1f) + (uint)CARRY4(uVar4,(uint)lVar1);
        if (param_4 == (int *)0x0) {
          return local_c;
        }
        *param_4 = param_1->current_link;
        return local_c;
      }
      lVar2 = _fetch_and_process_packet(param_1,(ogg_packet *)0x0,1,1);
      if (lVar2 == -2) {
        return 0;
      }
    } while (0 < lVar2);
  }
  return lVar2;
}
