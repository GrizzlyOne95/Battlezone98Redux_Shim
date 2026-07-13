/*
 * Entry: 004d9cae
 * Name: ScrapGauge::Render
 * Namespace: ScrapGauge
 * Signature: void Render(ScrapGauge * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ScrapGauge::Render(ScrapGauge *this)

{
  Team *this_00;
  float fVar1;
  long lVar2;
  long lVar3;
  char local_18 [16];
  uint local_8;
  
  fVar1 = spriteZ;
  this_00 = GameObject::userTeamList;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (400 < Device.Viewport.Width) {
    spriteZ = spriteZ + 0.1;
    DrawSprite(DisplayInterface::currentBuffer,this->scrapPanel,SCRAP_PANEL_POS.x,SCRAP_PANEL_POS.y,
               1);
  }
  Foreground_Color = DisplayInterface::colorBlue;
  spriteZ = fVar1;
  DrawSprite(DisplayInterface::currentBuffer,this->scrapTitle,SCRAP_TITLE_POS.x,SCRAP_TITLE_POS.y,5)
  ;
  Font_Set_Foreground(Default_Font,DisplayInterface::colorBlue);
  lVar2 = Team::GetMaxScrap(this_00);
  lVar3 = Team::GetScrap(this_00);
  sprintf(local_18,"%02d/%02d",lVar3,lVar2);
  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,SCRAP_GAUGE_POS.x,SCRAP_GAUGE_POS.y
                    ,local_18);
  if (400 < Device.Viewport.Width) {
    spriteZ = fVar1 + 0.1;
    DrawSprite(DisplayInterface::currentBuffer,this->pilotPanel,PILOT_PANEL_POS.x,PILOT_PANEL_POS.y,
               1);
    spriteZ = fVar1;
  }
  Foreground_Color = DisplayInterface::colorGreen;
  DrawSprite(DisplayInterface::currentBuffer,this->pilotTitle,PILOT_TITLE_POS.x,PILOT_TITLE_POS.y,5)
  ;
  Font_Set_Foreground(Default_Font,DisplayInterface::colorGreen);
  lVar2 = Team::GetMaxPilot(this_00);
  lVar3 = Team::GetPilot(this_00);
  sprintf(local_18,"%02d/%02d",lVar3,lVar2);
  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,PILOT_GAUGE_POS.x,PILOT_GAUGE_POS.y
                    ,local_18);
  return;
}
