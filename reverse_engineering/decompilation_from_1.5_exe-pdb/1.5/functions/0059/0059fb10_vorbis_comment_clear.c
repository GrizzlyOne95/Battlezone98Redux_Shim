/*
 * Entry: 0059fb10
 * Name: vorbis_comment_clear
 * Namespace: Global
 * Signature: void vorbis_comment_clear(vorbis_comment * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_comment_clear(vorbis_comment *param_1)

{
  int iVar1;
  
  if (param_1 != (vorbis_comment *)0x0) {
    if (param_1->user_comments != (char **)0x0) {
      iVar1 = 0;
      if (0 < param_1->comments) {
        do {
          if (param_1->user_comments[iVar1] != (char *)0x0) {
            free(param_1->user_comments[iVar1]);
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < param_1->comments);
      }
      free(param_1->user_comments);
    }
    if (param_1->comment_lengths != (int *)0x0) {
      free(param_1->comment_lengths);
    }
    if (param_1->vendor != (char *)0x0) {
      free(param_1->vendor);
    }
    param_1->user_comments = (char **)0x0;
    param_1->comment_lengths = (int *)0x0;
    param_1->comments = 0;
    param_1->vendor = (char *)0x0;
  }
  return;
}
