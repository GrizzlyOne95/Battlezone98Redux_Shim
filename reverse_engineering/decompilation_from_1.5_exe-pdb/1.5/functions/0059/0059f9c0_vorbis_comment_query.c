/*
 * Entry: 0059f9c0
 * Name: vorbis_comment_query
 * Namespace: Global
 * Signature: char * vorbis_comment_query(vorbis_comment * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

char * __cdecl vorbis_comment_query(vorbis_comment *param_1,char *param_2,int param_3)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  undefined2 *puVar8;
  int aiStack_1c [2];
  int local_8;
  
  local_8 = 0;
  pcVar1 = param_2 + 1;
  pcVar5 = param_2;
  do {
    cVar3 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar3 != '\0');
  aiStack_1c[1] = 0x59f9ea;
  iVar4 = -(int)(pcVar5 + (2 - (int)pcVar1));
  iVar7 = iVar4 - (int)param_2;
  do {
    cVar3 = *param_2;
    param_2[(int)(&stack0xffffffec + iVar7)] = cVar3;
    param_2 = param_2 + 1;
  } while (cVar3 != '\0');
  puVar8 = (undefined2 *)((int)aiStack_1c + iVar4 + 7);
  do {
    pcVar2 = (char *)((int)puVar8 + 1);
    puVar8 = (undefined2 *)((int)puVar8 + 1);
  } while (*pcVar2 != '\0');
  *puVar8 = 0x3d;
  iVar7 = 0;
  if (0 < param_1->comments) {
    do {
      *(char **)((int)aiStack_1c + iVar4 + 4) = pcVar5 + (1 - (int)pcVar1);
      *(undefined4 *)((int)aiStack_1c + iVar4) = 0x59fa2e;
      iVar6 = tagcompare(*(char **)((int)aiStack_1c + iVar4 + 4),
                         *(char **)(&stack0xffffffec + iVar4),*(int *)(&stack0xfffffff0 + iVar4));
      if (iVar6 == 0) {
        if (param_3 == local_8) {
          return param_1->user_comments[iVar7] + (int)(pcVar5 + (1 - (int)pcVar1));
        }
        local_8 = local_8 + 1;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < param_1->comments);
  }
  return (char *)0x0;
}
