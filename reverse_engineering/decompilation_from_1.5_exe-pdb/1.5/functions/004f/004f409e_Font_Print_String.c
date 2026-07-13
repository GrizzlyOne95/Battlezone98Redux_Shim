/*
 * Entry: 004f409e
 * Name: Font_Print_String
 * Namespace: Global
 * Signature: void Font_Print_String(FONT * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Font_Print_String(FONT *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,char *param_5)

{
  char cVar1;
  bool bVar2;
  ushort *puVar3;
  int iVar4;
  CHARACTER *pCVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  code *local_10;
  int local_8;
  
  local_8 = 0;
  bVar2 = false;
  if (indexChar0 < 0) {
    indexChar0 = GetSpriteIndex("char.0");
  }
  local_10 = JCharSprite;
  if ((param_1->type & 0x100U) == 0) {
    local_10 = CharSprite;
  }
  cVar1 = *param_5;
  iVar6 = param_3;
  puVar3 = (ushort *)param_5;
  if ((VIDEO_DEVICE *)param_2 == &Device) {
    while (cVar1 != '\0') {
      if (!bVar2) {
        do {
          if (iVar6 - param_3 < tabdefs[local_8]) break;
          if (tabdefs[local_8] == -1) {
            bVar2 = true;
          }
          local_8 = local_8 + 1;
        } while (!bVar2);
      }
      param_5 = (char *)puVar3;
      if (cVar1 == '\t') {
        if (bVar2) {
          iVar6 = iVar6 + 0x20;
        }
        else {
          iVar6 = tabdefs[local_8] + param_3;
        }
      }
      else if (cVar1 == '\n') {
        param_4 = param_4 + 2 + param_1->char_height;
        iVar6 = param_3;
      }
      else {
        if (useD3D == 0) {
          if (Device.Viewport.Bit_Depth == BYTES_FORMAT) {
            Font_Print_Character(param_1,&Device.Viewport,iVar6,param_4,*puVar3);
          }
          else {
            Font_Print_Character_8to16(param_1,&Device.Viewport,iVar6,param_4,*puVar3);
          }
        }
        else {
          iVar9 = 0x200005;
          iVar7 = iVar6;
          iVar8 = param_4;
          iVar4 = (*local_10)(puVar3);
          DrawSprite(&Device.Viewport,iVar4,iVar7,iVar8,iVar9);
        }
        pCVar5 = GetCharacterAddress(param_1,*puVar3);
        iVar6 = iVar6 + pCVar5->Width;
      }
      IncString(&param_5);
      puVar3 = (ushort *)param_5;
      cVar1 = *param_5;
    }
  }
  else {
    while (cVar1 != '\0') {
      if (!bVar2) {
        do {
          if (iVar6 - param_3 < tabdefs[local_8]) break;
          if (tabdefs[local_8] == -1) {
            bVar2 = true;
          }
          local_8 = local_8 + 1;
        } while (!bVar2);
      }
      param_5 = (char *)puVar3;
      if (cVar1 == '\t') {
        if (bVar2) {
          iVar6 = iVar6 + 0x20;
        }
        else {
          iVar6 = tabdefs[local_8] + param_3;
        }
      }
      else if (cVar1 == '\n') {
        param_4 = param_4 + 2 + param_1->char_height;
        iVar6 = param_3;
      }
      else {
        Font_Print_Character(param_1,param_2,iVar6,param_4,*puVar3);
        pCVar5 = GetCharacterAddress(param_1,*puVar3);
        iVar6 = iVar6 + pCVar5->Width;
      }
      IncString(&param_5);
      puVar3 = (ushort *)param_5;
      cVar1 = *param_5;
    }
  }
  return;
}
