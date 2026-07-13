/*
 * Entry: 0059f830
 * Name: vorbis_comment_add
 * Namespace: Global
 * Signature: void vorbis_comment_add(vorbis_comment * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_comment_add(vorbis_comment *param_1,char *param_2)

{
  char cVar1;
  char **ppcVar2;
  int *piVar3;
  char *pcVar4;
  
  ppcVar2 = realloc(param_1->user_comments,param_1->comments * 4 + 8);
  param_1->user_comments = ppcVar2;
  piVar3 = realloc(param_1->comment_lengths,param_1->comments * 4 + 8);
  param_1->comment_lengths = piVar3;
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  piVar3[param_1->comments] = (int)pcVar4 - (int)(param_2 + 1);
  pcVar4 = malloc(param_1->comment_lengths[param_1->comments] + 1);
  param_1->user_comments[param_1->comments] = pcVar4;
  pcVar4 = param_1->user_comments[param_1->comments];
  do {
    cVar1 = *param_2;
    *pcVar4 = cVar1;
    param_2 = param_2 + 1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  param_1->comments = param_1->comments + 1;
  param_1->user_comments[param_1->comments] = (char *)0x0;
  return;
}
