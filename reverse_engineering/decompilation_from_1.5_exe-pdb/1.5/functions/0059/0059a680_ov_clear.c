/*
 * Entry: 0059a680
 * Name: ov_clear
 * Namespace: Global
 * Signature: int ov_clear(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_clear(OggVorbis_File *param_1)

{
  int local_8;
  
  if (param_1 != (OggVorbis_File *)0x0) {
    vorbis_block_clear(&param_1->vb);
    vorbis_dsp_clear(&param_1->vd);
    ogg_stream_clear(&param_1->os);
    if ((param_1->vi != (vorbis_info *)0x0) && (param_1->links != 0)) {
      for (local_8 = 0; local_8 < param_1->links; local_8 = local_8 + 1) {
        vorbis_info_clear(param_1->vi + local_8);
        vorbis_comment_clear(param_1->vc + local_8);
      }
      free(param_1->vi);
      free(param_1->vc);
    }
    if (param_1->dataoffsets != (long64 *)0x0) {
      free(param_1->dataoffsets);
    }
    if (param_1->pcmlengths != (long64 *)0x0) {
      free(param_1->pcmlengths);
    }
    if (param_1->serialnos != (long *)0x0) {
      free(param_1->serialnos);
    }
    if (param_1->offsets != (long64 *)0x0) {
      free(param_1->offsets);
    }
    ogg_sync_clear(&param_1->oy);
    if ((param_1->datasource != (void *)0x0) &&
       ((param_1->callbacks).close_func != (_func___cdecl_int_void_ptr *)0x0)) {
      (*(param_1->callbacks).close_func)(param_1->datasource);
    }
    memset(param_1,0,0x2d0);
  }
  return 0;
}
