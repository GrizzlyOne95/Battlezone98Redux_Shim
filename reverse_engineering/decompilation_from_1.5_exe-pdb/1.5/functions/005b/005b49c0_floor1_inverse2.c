/*
 * Entry: 005b49c0
 * Name: floor1_inverse2
 * Namespace: Global
 * Signature: int floor1_inverse2(vorbis_block * param_1, void * param_2, void * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl floor1_inverse2(vorbis_block *param_1,void *param_2,void *param_3,float *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *unaff_EDI;
  int iVar8;
  int local_8;
  int local_4;
  
  iVar1 = *(int *)((int)param_2 + 0x510);
  iVar8 = 0;
  iVar7 = *(int *)((int)param_1->vd->vi->codec_setup + param_1->W * 4) / 2;
  if (param_3 != (void *)0x0) {
    iVar5 = *(int *)(iVar1 + 0x340) * *(int *)param_3;
    local_8 = 0;
    if (iVar5 < 0) {
      iVar5 = 0;
    }
    else if (0xff < iVar5) {
      iVar5 = 0xff;
    }
    local_4 = 1;
    if (1 < *(int *)((int)param_2 + 0x504)) {
      param_1 = (vorbis_block *)((int)param_2 + 0x108);
      iVar6 = iVar5;
      do {
        uVar2 = *(uint *)((int)param_3 + (int)param_1->pcm * 4);
        uVar3 = uVar2 & 0x7fff;
        iVar5 = iVar6;
        if (uVar3 == uVar2) {
          iVar8 = *(int *)(iVar1 + 0x344 + (int)param_1->pcm * 4);
          iVar5 = *(int *)(iVar1 + 0x340) * uVar3;
          if (iVar5 < 0) {
            iVar5 = 0;
          }
          else if (0xff < iVar5) {
            iVar5 = 0xff;
          }
          render_line(iVar7,local_8,iVar8,iVar6,(int)param_4,unaff_EDI);
          local_8 = iVar8;
        }
        param_1 = (vorbis_block *)&param_1->opb;
        local_4 = local_4 + 1;
        iVar6 = iVar5;
      } while (local_4 < *(int *)((int)param_2 + 0x504));
    }
    if (iVar8 < iVar7) {
      if (3 < iVar7 - iVar8) {
        iVar6 = ((iVar7 - iVar8) - 4U >> 2) + 1;
        iVar1 = iVar8 + 2;
        iVar8 = iVar8 + iVar6 * 4;
        pfVar4 = param_4 + iVar1;
        do {
          iVar6 = iVar6 + -1;
          pfVar4[-2] = FLOOR1_fromdB_LOOKUP[iVar5] * pfVar4[-2];
          pfVar4[-1] = FLOOR1_fromdB_LOOKUP[iVar5] * pfVar4[-1];
          *pfVar4 = FLOOR1_fromdB_LOOKUP[iVar5] * *pfVar4;
          pfVar4[1] = pfVar4[1] * FLOOR1_fromdB_LOOKUP[iVar5];
          pfVar4 = pfVar4 + 4;
        } while (iVar6 != 0);
      }
      for (; iVar8 < iVar7; iVar8 = iVar8 + 1) {
        param_4[iVar8] = FLOOR1_fromdB_LOOKUP[iVar5] * param_4[iVar8];
      }
    }
    return 1;
  }
  memset(param_4,0,iVar7 * 4);
  return 0;
}
