/*
 * Entry: 0059fb80
 * Name: vorbis_info_blocksize
 * Namespace: Global
 * Signature: int vorbis_info_blocksize(vorbis_info * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_info_blocksize(vorbis_info *param_1,int param_2)

{
  if (param_1->codec_setup != (void *)0x0) {
    return *(int *)((int)param_1->codec_setup + param_2 * 4);
  }
  return -1;
}
