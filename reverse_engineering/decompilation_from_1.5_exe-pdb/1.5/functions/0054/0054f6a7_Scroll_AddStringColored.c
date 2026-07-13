/*
 * Entry: 0054f6a7
 * Name: Scroll_AddStringColored
 * Namespace: Global
 * Signature: void Scroll_AddStringColored(void * param_1, char * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_AddStringColored(void *param_1,char *param_2,ulong param_3)

{
  int iVar1;
  char *pcVar2;
  long lVar3;
  CHARACTER *pCVar4;
  int iVar5;
  SCROLL_REGION *unaff_ESI;
  char *_Dest;
  float fVar6;
  uint local_8;
  
  iVar1 = *(int *)((int)param_1 + 8);
  if (((*(byte *)(iVar1 + 0x60) & 8) == 0) || (*(int *)(iVar1 + 0x20) != *(int *)(iVar1 + 0x10) + 1)
     ) {
    lVar3 = Get_Closest_RGB_Entry
                      ((float)(param_3 & 0xff) * 0.003921569,
                       (float)(param_3 >> 8 & 0xff) * 0.003921569,
                       (float)(param_3 >> 0x10 & 0xff) * 0.003921569);
    _Dest = (char *)(*(int *)(iVar1 + 0x20) * 0x58 + *(int *)(iVar1 + 0x28));
    local_8 = 0;
    param_1 = param_2;
    if (*param_2 != '\0') {
      do {
        pCVar4 = GetCharacterAddress(Default_Font,(short)*(char *)param_1);
        local_8 = local_8 + pCVar4->Width;
        pcVar2 = param_1;
        if ((param_1 == param_2 + *(int *)(iVar1 + 0x14)) || (*(uint *)(iVar1 + 8) < local_8)) {
          for (; param_2 <= pcVar2; pcVar2 = pcVar2 + -1) {
            iVar5 = isspace((int)*pcVar2);
            if (iVar5 != 0) {
              param_1 = pcVar2 + 1;
              break;
            }
          }
          strncpy(_Dest,param_2,(int)param_1 - (int)param_2);
          _Dest[(int)param_1 - (int)param_2] = '\0';
          fVar6 = Get_TimeLocal();
          *(float *)(_Dest + 0x50) = fVar6 + *(float *)(iVar1 + 0x58);
          *(long *)(_Dest + 0x54) = lVar3;
          Scroll_AdvanceLine(unaff_ESI);
          if (((*(uint *)(iVar1 + 0x60) & 8) != 0) &&
             (*(int *)(iVar1 + 0x20) == *(int *)(iVar1 + 0x10) + 1)) {
            return;
          }
          _Dest = (char *)(*(int *)(iVar1 + 0x20) * 0x58 + *(int *)(iVar1 + 0x28));
          local_8 = 0;
          *(uint *)(iVar1 + 0x60) = *(uint *)(iVar1 + 0x60) | 0x80000000;
          param_2 = param_1;
        }
        param_1 = (void *)((int)param_1 + 1);
      } while (*(char *)param_1 != '\0');
      if (*param_2 != '\0') {
        strncpy(_Dest,param_2,*(size_t *)(iVar1 + 0x14));
        _Dest[*(int *)(iVar1 + 0x14)] = '\0';
        fVar6 = Get_TimeLocal();
        *(float *)(_Dest + 0x50) = fVar6 + *(float *)(iVar1 + 0x58);
        *(long *)(_Dest + 0x54) = lVar3;
        Scroll_AdvanceLine(unaff_ESI);
        *(uint *)(iVar1 + 0x60) = *(uint *)(iVar1 + 0x60) | 0x80000000;
      }
    }
  }
  return;
}
