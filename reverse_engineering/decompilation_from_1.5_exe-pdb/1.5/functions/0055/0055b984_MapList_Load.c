/*
 * Entry: 0055b984
 * Name: MapList::Load
 * Namespace: MapList
 * Signature: void Load(MapList * this, HWND__ * param_1, TextWindow * param_2, HWND__ * param_3, TextLabel * param_4, VehicleList * param_5, TextWindow * param_6, OptionBox * param_7, TextLabel * param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
MapList::Load(MapList *this,HWND__ *param_1,TextWindow *param_2,HWND__ *param_3,TextLabel *param_4,
             VehicleList *param_5,TextWindow *param_6,OptionBox *param_7,TextLabel *param_8)

{
  this->playerLimit = param_7;
  this->vehDesc = (TextWindow *)param_4;
  this->vehicleList = param_5;
  this->selectedItem = (int)param_6;
  this->hPlayerLimit = param_3;
  this->mapDesc = param_2;
  (this->rect).left = (long)param_8;
  this->hwnd = param_1;
  Load(this,"netmis.txt");
  StartAnim(this);
  return;
}
