/*
 * Entry: 0059f810
 * Name: vorbis_comment_init
 * Namespace: Global
 * Signature: void vorbis_comment_init(vorbis_comment * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_comment_init(vorbis_comment *param_1)

{
  param_1->user_comments = (char **)0x0;
  param_1->comment_lengths = (int *)0x0;
  param_1->comments = 0;
  param_1->vendor = (char *)0x0;
  return;
}
