/*
 * Entry: 005045d3
 * Name: EnableSkipLines
 * Namespace: Global
 * Signature: void EnableSkipLines(CAMERA * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EnableSkipLines(CAMERA *param_1,int param_2,int param_3)

{
  float fVar1;
  uchar uVar2;
  int iVar3;
  _GRAPHIC_BUFFER *p_Var4;
  CAMERA *pCVar5;
  _GRAPHIC_BUFFER *p_Var6;
  _GRAPHIC_BUFFER *p_Var7;
  CAMERA *pCVar8;
  
  uVar2 = UserPref_lineskip();
  if (uVar2 != '\0') {
    if (param_2 == 0) {
      pCVar5 = &savedCamera;
      pCVar8 = param_1;
      for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
        pCVar8->Orig_x = pCVar5->Orig_x;
        pCVar5 = (CAMERA *)&pCVar5->Orig_y;
        pCVar8 = (CAMERA *)&pCVar8->Orig_y;
      }
      p_Var6 = &savedBuffer;
      p_Var4 = param_1->Buffer;
      for (iVar3 = 0xd; TerrainIntensity = savedIntensity, iVar3 != 0; iVar3 = iVar3 + -1) {
        p_Var4->Width = p_Var6->Width;
        p_Var6 = (_GRAPHIC_BUFFER *)&p_Var6->Height;
        p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
      }
    }
    else {
      p_Var6 = param_1->Buffer;
      pCVar5 = param_1;
      pCVar8 = &savedCamera;
      for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
        pCVar8->Orig_x = pCVar5->Orig_x;
        pCVar5 = (CAMERA *)&pCVar5->Orig_y;
        pCVar8 = (CAMERA *)&pCVar8->Orig_y;
      }
      p_Var4 = p_Var6;
      p_Var7 = &savedBuffer;
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        p_Var7->Width = p_Var4->Width;
        p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
        p_Var7 = (_GRAPHIC_BUFFER *)&p_Var7->Height;
      }
      p_Var6->Width = p_Var6->Width << 1;
      param_1->Buffer->Height = param_1->Buffer->Height / 2;
      (param_1->Buffer->Pane).y0 = (param_1->Buffer->Pane).y0 / 2 & 0xfffffffe;
      p_Var6 = param_1->Buffer;
      iVar3 = (p_Var6->Pane).y0;
      (p_Var6->Pane).y1 = (((p_Var6->Pane).y1 - iVar3) + 1) / 2 + -1 + iVar3;
      param_1->Const_y = param_1->Const_y * 0.5;
      param_1->Orig_y = param_1->Orig_y * 0.5;
      param_1->Bottom = param_1->Bottom * 0.5;
      param_1->Top = param_1->Top * 0.5;
      savedIntensity = TerrainIntensity;
      fVar1 = TerrainIntensity * STEP;
      TerrainIntensity = 1.0;
      if (fVar1 <= 1.0) {
        TerrainIntensity = fVar1;
      }
    }
  }
  return;
}
