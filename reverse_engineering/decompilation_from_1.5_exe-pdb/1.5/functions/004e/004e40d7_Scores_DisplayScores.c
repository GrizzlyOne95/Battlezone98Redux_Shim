/*
 * Entry: 004e40d7
 * Name: Scores_DisplayScores
 * Namespace: Global
 * Signature: void Scores_DisplayScores(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scores_DisplayScores(void)

{
  int iVar1;
  long unaff_EBX;
  FONT *pFVar2;
  long unaff_ESI;
  char *unaff_EDI;
  char *pcVar3;
  FONT *pFVar4;
  _GRAPHIC_BUFFER *local_10;
  int local_8;
  
  pFVar2 = Default_Font;
  iVar1 = IsJapanese();
  if (iVar1 != 0) {
    pFVar2 = J_Font;
  }
  if (score_show != 0) {
    Font_Set_Tabs(6,tabdefs);
    if (score_has_ping == 0) {
      if (king_of_the_hill_game == 0) {
        if (stratgy_game == 0) {
          pcVar3 = defaultBuf;
        }
        else {
          pcVar3 = strategyBuf;
        }
      }
      else {
        pcVar3 = kingBuf;
      }
    }
    else if (king_of_the_hill_game == 0) {
      if (stratgy_game == 0) {
        pcVar3 = defaultPBuf;
      }
      else {
        pcVar3 = strategyPBuf;
      }
    }
    else {
      pcVar3 = kingPBuf;
    }
    Font_Print_String_Shadowed
              ((FONT *)&Device,(_GRAPHIC_BUFFER *)pcVar3,DisplayInterface::colorWhite,unaff_ESI,
               unaff_EDI,unaff_EBX);
    local_8 = 0;
    if (0 < score_count) {
      local_10 = (_GRAPHIC_BUFFER *)score_text;
      do {
        pcVar3 = (char *)score_color[local_8];
        pFVar4 = pFVar2;
        Font_Set_Foreground(pFVar2,(long)pcVar3);
        Font_Print_String_Shadowed
                  ((FONT *)&Device,local_10,score_color[local_8],(long)pFVar4,pcVar3,unaff_ESI);
        local_10 = (_GRAPHIC_BUFFER *)&local_10[1].Pane;
        local_8 = local_8 + 1;
      } while (local_8 < score_count);
    }
  }
  return;
}
