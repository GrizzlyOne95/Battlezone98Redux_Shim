/*
 * Entry: 0059fe30
 * Name: _vorbis_unpack_comment
 * Namespace: Global
 * Signature: int _vorbis_unpack_comment(vorbis_comment * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_unpack_comment(vorbis_comment *param_1,oggpack_buffer *param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  char **ppcVar4;
  int *piVar5;
  int iVar6;
  int unaff_EBX;
  char *unaff_EBP;
  vorbis_comment *unaff_ESI;
  oggpack_buffer *unaff_EDI;
  oggpack_buffer *_Count;
  char *pcVar7;
  
  iVar1 = oggpack_read(param_1,0x20);
  if ((-1 < iVar1) && (iVar1 <= (int)(param_1[1].user_comments + -2))) {
    _Count = (oggpack_buffer *)(iVar1 + 1);
    pcVar7 = (char *)0x1;
    pcVar2 = calloc((size_t)_Count,1);
    unaff_ESI->vendor = pcVar2;
    _v_readstring(_Count,pcVar7,(int)unaff_EDI);
    iVar1 = oggpack_read(param_1,0x20);
    if (-1 < iVar1) {
      iVar3 = oggpack_bytes(param_1);
      if (iVar1 <= (int)param_1[1].user_comments - iVar3 >> 2) {
        unaff_ESI->comments = iVar1;
        ppcVar4 = calloc(iVar1 + 1,4);
        unaff_ESI->user_comments = ppcVar4;
        piVar5 = calloc(unaff_ESI->comments + 1,4);
        iVar1 = 0;
        unaff_ESI->comment_lengths = piVar5;
        if (0 < unaff_ESI->comments) {
          do {
            iVar3 = oggpack_read(param_1,0x20);
            if (iVar3 < 0) goto LAB_0059ff26;
            iVar6 = oggpack_bytes(param_1);
            if ((int)param_1[1].user_comments - iVar6 < iVar3) goto LAB_0059ff26;
            unaff_ESI->comment_lengths[iVar1] = iVar3;
            pcVar2 = calloc(iVar3 + 1,1);
            unaff_ESI->user_comments[iVar1] = pcVar2;
            _v_readstring(unaff_EDI,unaff_EBP,unaff_EBX);
            iVar1 = iVar1 + 1;
          } while (iVar1 < unaff_ESI->comments);
        }
        iVar1 = oggpack_read(param_1,1);
        if (iVar1 == 1) {
          return 0;
        }
      }
    }
  }
LAB_0059ff26:
  vorbis_comment_clear(unaff_ESI);
  return -0x85;
}
