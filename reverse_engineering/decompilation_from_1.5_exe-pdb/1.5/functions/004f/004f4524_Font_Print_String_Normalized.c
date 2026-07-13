/*
 * Entry: 004f4524
 * Name: Font_Print_String_Normalized
 * Namespace: Global
 * Signature: void Font_Print_String_Normalized(FONT * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Font_Print_String_Normalized
          (FONT *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,char *param_5)

{
  char cVar1;
  float fVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar6;
  CHARACTER *pCVar7;
  int extraout_EAX_03;
  int extraout_EAX_04;
  int extraout_EAX_05;
  int extraout_EAX_06;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  code *local_1c;
  int local_10;
  
  local_10 = 0;
  bVar3 = false;
  if (indexChar0 < 0) {
    indexChar0 = GetSpriteIndex("char.0");
  }
  local_1c = JCharSprite;
  if ((param_1->type & 0x100U) == 0) {
    local_1c = CharSprite;
  }
  iVar5 = (Device.Viewport.Pane.x1 - Device.Viewport.Pane.x0) + 1;
  if ((VIDEO_DEVICE *)param_2 == &Device) {
    _ftol2_sse();
    _ftol2_sse();
    iVar8 = extraout_EAX_00;
    iVar9 = extraout_EAX;
    while (pcVar4 = param_5, cVar1 = *param_5, cVar1 != '\0') {
      if (!bVar3) {
        do {
          fVar2 = (float)tabdefs[local_10] * (float)iVar5 * 0.0015625;
          if (fVar2 < (float)(iVar9 - extraout_EAX) == (fVar2 == (float)(iVar9 - extraout_EAX)))
          break;
          if (tabdefs[local_10] == -1) {
            bVar3 = true;
          }
          local_10 = local_10 + 1;
        } while (!bVar3);
      }
      if (cVar1 == '\t') {
        if (bVar3) {
          _ftol2_sse();
          iVar9 = iVar9 + extraout_EAX_02;
        }
        else {
          _ftol2_sse();
          iVar9 = extraout_EAX_01;
        }
      }
      else if (cVar1 == '\n') {
        iVar8 = iVar8 + 2 + param_1->char_height;
        iVar9 = extraout_EAX;
      }
      else {
        if (useD3D == 0) {
          if (Device.Viewport.Bit_Depth == BYTES_FORMAT) {
            Font_Print_Character(param_1,&Device.Viewport,iVar9,iVar8,*(ushort *)param_5);
          }
          else {
            Font_Print_Character_8to16(param_1,&Device.Viewport,iVar9,iVar8,*(ushort *)param_5);
          }
        }
        else {
          iVar12 = 0x200005;
          iVar10 = iVar9;
          iVar11 = iVar8;
          iVar6 = (*local_1c)(param_5);
          DrawSprite(&Device.Viewport,iVar6,iVar10,iVar11,iVar12);
        }
        pCVar7 = GetCharacterAddress(param_1,*(ushort *)pcVar4);
        iVar9 = iVar9 + pCVar7->Width;
      }
      IncString(&param_5);
    }
  }
  else {
    _ftol2_sse();
    _ftol2_sse();
    iVar8 = extraout_EAX_04;
    iVar9 = extraout_EAX_03;
    while (pcVar4 = param_5, cVar1 = *param_5, cVar1 != '\0') {
      if (!bVar3) {
        do {
          fVar2 = (float)tabdefs[local_10] * (float)iVar5 * 0.0015625;
          if (fVar2 < (float)(iVar9 - extraout_EAX_03) ==
              (fVar2 == (float)(iVar9 - extraout_EAX_03))) break;
          if (tabdefs[local_10] == -1) {
            bVar3 = true;
          }
          local_10 = local_10 + 1;
        } while (!bVar3);
      }
      if (cVar1 == '\t') {
        if (bVar3) {
          _ftol2_sse();
          iVar9 = iVar9 + extraout_EAX_06;
        }
        else {
          _ftol2_sse();
          iVar9 = extraout_EAX_05;
        }
      }
      else if (cVar1 == '\n') {
        iVar8 = iVar8 + 2 + param_1->char_height;
        iVar9 = extraout_EAX_03;
      }
      else {
        Font_Print_Character(param_1,param_2,iVar9,iVar8,*(ushort *)param_5);
        pCVar7 = GetCharacterAddress(param_1,*(ushort *)pcVar4);
        iVar9 = iVar9 + pCVar7->Width;
      }
      IncString(&param_5);
    }
  }
  return;
}
