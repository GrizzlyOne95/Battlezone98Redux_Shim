/*
 * Entry: 004f4289
 * Name: Font_Read
 * Namespace: Global
 * Signature: FONT * Font_Read(MILES_FONT_INFO * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

FONT * __cdecl Font_Read(MILES_FONT_INFO *param_1)

{
  int *piVar1;
  FILE *_File;
  FONT *pFVar2;
  int iVar3;
  FONT *pFVar4;
  size_t _Size;
  int iVar5;
  int aiStack_86c6c [10000];
  undefined1 auStack_7d02c [4];
  size_t sStack_7d028;
  size_t sStack_7d024;
  MILES_FONT_INFO *pMStack_7d01c;
  FILE *pFStack_7d018;
  size_t sStack_7d014;
  int iStack_7d010;
  FONT *pFStack_7d00c;
  size_t sStack_7d008;
  undefined1 auStack_7d004 [512000];
  
  pMStack_7d01c = param_1;
  pFStack_7d00c = (FONT *)(uint)((param_1->type & 0x100U) != 0);
  _File = fopen(param_1->name,"rb");
  pFVar2 = (FONT *)0x0;
  if (_File != (FILE *)0x0) {
    pFStack_7d018 = _File;
    fread(auStack_7d02c,4,4,_File);
    fread(aiStack_86c6c,sStack_7d028,4,_File);
    _Size = 0;
    iStack_7d010 = 0;
    if (0 < (int)sStack_7d028) {
      do {
        fread((size_t *)((int)&sStack_7d008 + _Size),1,4,pFStack_7d018);
        sStack_7d014 = *(size_t *)((int)&sStack_7d008 + _Size);
        if (sStack_7d014 != 0) {
          if (pFStack_7d00c != (FONT *)0x0) {
            sStack_7d014 = (8 < (int)sStack_7d014) + 1;
          }
          fread(auStack_7d004 + _Size,sStack_7d014,sStack_7d024,pFStack_7d018);
        }
        iStack_7d010 = iStack_7d010 + 1;
        _Size = _Size + 4 + sStack_7d024 * sStack_7d014;
        param_1 = pMStack_7d01c;
      } while (iStack_7d010 < (int)sStack_7d028);
    }
    pFVar2 = malloc(_Size + 0x20c + sStack_7d028 * 4);
    if (pFVar2 == (FONT *)0x0) {
      fclose(pFStack_7d018);
      pFVar2 = (FONT *)0x0;
    }
    else {
      pFVar2->char_count = sStack_7d028;
      pFVar2->char_height = sStack_7d024;
      sStack_7d014 = (int)(pFVar2[1].Back_Foreground + -1) + 0xf4 + sStack_7d028 * 4;
      iVar3 = 0;
      if (0 < (int)sStack_7d028) {
        pFVar4 = pFVar2 + 1;
        do {
          piVar1 = aiStack_86c6c + iVar3;
          iVar3 = iVar3 + 1;
          pFVar4->type = (*piVar1 - aiStack_86c6c[0]) + sStack_7d014;
          pFVar4 = (FONT *)&pFVar4->char_count;
        } while (iVar3 < (int)sStack_7d028);
      }
      memmove((void *)((int)(pFVar2[1].Back_Foreground + -1) + 0xf4 + sStack_7d028 * 4),
              &sStack_7d008,_Size);
      Font_Set_Background(pFVar2,-1);
      Font_Set_Foreground(pFVar2,0xf);
      if ((pFStack_7d00c == (FONT *)0x0) && (iStack_7d010 = 0, 0 < (int)sStack_7d028)) {
        pFStack_7d00c = pFVar2 + 1;
        do {
          piVar1 = (int *)pFStack_7d00c->type;
          iVar3 = pFVar2->char_height * *piVar1;
          iVar5 = 0;
          if (0 < iVar3) {
            do {
              *(bool *)(iVar5 + 4 + (int)piVar1) = *(char *)(iVar5 + 4 + (int)piVar1) != -1;
              iVar5 = iVar5 + 1;
            } while (iVar5 < iVar3);
          }
          iStack_7d010 = iStack_7d010 + 1;
          pFStack_7d00c = (FONT *)&pFStack_7d00c->char_count;
          param_1 = pMStack_7d01c;
        } while (iStack_7d010 < (int)sStack_7d028);
      }
      fclose(pFStack_7d018);
      pFVar2->type = param_1->type;
    }
  }
  return pFVar2;
}
