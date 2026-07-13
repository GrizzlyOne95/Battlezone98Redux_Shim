/*
 * Entry: 0054db23
 * Name: DrawMenuObject
 * Namespace: Global
 * Signature: void DrawMenuObject(_menu_item * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DrawMenuObject(_menu_item *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  HFONT__ *h;
  char *pcVar3;
  int iVar4;
  long lVar5;
  tagSIZE local_3c;
  int local_34;
  int local_30;
  tagRECT local_2c;
  char *local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  h = GetMenuFont(param_1->flags);
  if (h != (HFONT__ *)0x0) {
    SelectObject((HDC)mInfo.dc,h);
  }
  local_2c.left = (param_1->itemRect).left;
  local_2c.top = (param_1->itemRect).top;
  local_2c.right = (param_1->itemRect).right;
  local_2c.bottom = (param_1->itemRect).bottom;
  if (param_2 != 0) {
    Rectangle((HDC)mInfo.dc,local_2c.left,local_2c.top,local_2c.right,local_2c.bottom);
  }
  local_1c = param_1->itemText;
  if (local_1c != (char *)0x0) {
    if ((UserProfilePtr->graphicDetail).resolution < 6) {
      local_2c.left = local_2c.left + 3;
      local_2c.top = local_2c.top + 3;
      lVar5 = 0x18;
    }
    else {
      local_2c.left = local_2c.left + 1;
      local_2c.top = local_2c.top + 1;
      lVar5 = 0xd;
    }
    DrawWrappedText(mInfo.dc,&local_2c,local_1c,lVar5,0,(_GRAPHIC_BUFFER *)0x0);
    local_1c = (char *)0x0;
  }
  local_2c.left = (param_1->choiceRect).left;
  local_2c.top = (param_1->choiceRect).top;
  local_2c.right = (param_1->choiceRect).right;
  local_2c.bottom = (param_1->choiceRect).bottom;
  if (((param_1->flags & 0x60U) == 0) || (param_1->curChoice == 0)) {
    if ((param_1->flags & 0x180U) != 0) {
      if (param_1->curChoice == 0) {
        local_1c = "Off";
      }
      else {
        local_1c = local_18;
        sprintf(local_1c,"%d.00",param_1->curChoice);
        if ((param_1->flags & 0x100U) == 0) {
          iVar4 = (param_1->itemRect).left;
          iVar2 = (param_1->itemRect).top;
          if ((UserProfilePtr->graphicDetail).resolution < 6) {
            iVar4 = iVar4 + 5;
            lVar5 = iVar2 + 0x1c;
            local_34 = 0x11;
          }
          else {
            iVar4 = iVar4 + 1;
            lVar5 = iVar2 + 10;
            local_34 = 7;
          }
          local_30 = 0;
          if (0 < param_1->curChoice) {
            do {
              Graphic_Copy_Bitmap(&mInfo.textGB,&mInfo.cmGB,iVar4,lVar5,TRANSPARENT_PIXELS);
              iVar4 = iVar4 + local_34;
              local_30 = local_30 + 1;
            } while (local_30 < param_1->curChoice);
          }
        }
      }
      goto LAB_0054dca4;
    }
    if (param_1->choiceText != (char **)0x0) {
      local_1c = param_1->choiceText[param_1->curChoice];
    }
  }
  else {
    Graphic_Copy_Bitmap(&mInfo.textGB,&mInfo.cmGB,local_2c.left,local_2c.top,TRANSPARENT_PIXELS);
  }
  if (local_1c == (char *)0x0) {
    return;
  }
LAB_0054dca4:
  pcVar3 = local_1c;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  GetTextExtentPoint32A((HDC)mInfo.dc,local_1c,(int)pcVar3 - (int)(local_1c + 1),&local_3c);
  if (local_2c.right - local_2c.left < local_3c.cx) {
    local_2c.left = local_2c.right - local_3c.cx;
  }
  pcVar3 = local_1c;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  TextOutA((HDC)mInfo.dc,local_2c.left,local_2c.top,local_1c,(int)pcVar3 - (int)(local_1c + 1));
  return;
}
