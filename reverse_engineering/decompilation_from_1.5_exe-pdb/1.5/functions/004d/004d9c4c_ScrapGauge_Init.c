/*
 * Entry: 004d9c4c
 * Name: ScrapGauge::Init
 * Namespace: ScrapGauge
 * Signature: void Init(ScrapGauge * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScrapGauge::Init(ScrapGauge *this)

{
  int iVar1;
  
  iVar1 = GetSpriteIndex("Scrap");
  this->scrapTitle = iVar1;
  iVar1 = GetSpriteIndex("scrap_panel");
  this->scrapPanel = iVar1;
  iVar1 = GetSpriteIndex("Pilot");
  this->pilotTitle = iVar1;
  iVar1 = GetSpriteIndex("pilot_panel");
  this->pilotPanel = iVar1;
  return;
}
