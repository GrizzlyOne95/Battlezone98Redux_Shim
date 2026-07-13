/*
 * Entry: 0059bed0
 * Name: ov_halfrate
 * Namespace: Global
 * Signature: int ov_halfrate(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_halfrate(OggVorbis_File *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_8;
  
  if (param_1->vi == (vorbis_info *)0x0) {
    iVar2 = -0x83;
  }
  else {
    if (3 < param_1->ready_state) {
      vorbis_dsp_clear(&param_1->vd);
      vorbis_block_clear(&param_1->vb);
      param_1->ready_state = 3;
      if (-1 < *(int *)((int)&param_1->pcm_offset + 4)) {
        uVar1 = *(undefined4 *)((int)&param_1->pcm_offset + 4);
        *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
        *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
        ov_pcm_seek(param_1,CONCAT44(param_1,uVar1));
      }
    }
    for (local_8 = 0; local_8 < param_1->links; local_8 = local_8 + 1) {
      iVar2 = vorbis_synthesis_halfrate(param_1->vi + local_8,param_2);
      if (iVar2 != 0) {
        if (param_2 != 0) {
          ov_halfrate(param_1,0);
        }
        return -0x83;
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}
