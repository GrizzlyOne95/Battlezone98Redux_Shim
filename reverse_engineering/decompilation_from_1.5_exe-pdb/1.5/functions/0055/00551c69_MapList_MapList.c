/*
 * Entry: 00551c69
 * Name: MapList::MapList
 * Namespace: MapList
 * Signature: MapList * MapList(MapList * this, HWND__ * param_1, HWND__ * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MapList * __thiscall MapList::MapList(MapList *this,HWND__ *param_1,HWND__ *param_2)

{
  this->hPlayerList = param_2;
  this->vehNameLabel = (TextLabel *)0x0;
  this->hDlg = param_1;
  this->count = 0;
  this->hwnd = (HWND__ *)0x0;
  this->playerLimit = (OptionBox *)0x0;
  this->vehDesc = (TextWindow *)0x0;
  this->selectedItem = 0;
  this->hPlayerLimit = (HWND__ *)0x0;
  this->mapDesc = (TextWindow *)0x0;
  this->vehicleList = (VehicleList *)0x0;
  this[1].hPlayerList = (HWND__ *)0x0;
  this->s = (_s *)0x0;
  this->shellBitmap = (ShellBitmap *)0x0;
  (this->rect).left = 0;
  this->yPos = 0xc9;
  (this->mop).dwCallback = 0x3f;
  (this->rect).top = 0xc9;
  (this->rect).bottom = 0x135;
  (this->rect).right = 0x3f;
  this->xPos = 0x98;
  return this;
}
