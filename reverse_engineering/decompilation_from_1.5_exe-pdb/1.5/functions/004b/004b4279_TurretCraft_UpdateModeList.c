/*
 * Entry: 004b4279
 * Name: TurretCraft::UpdateModeList
 * Namespace: TurretCraft
 * Signature: void UpdateModeList(TurretCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::UpdateModeList(TurretCraft *this)

{
  int *this_00;
  
  this_00 = &this->_padding_;
  ModeList::SetMode((ModeList *)this_00,0,1,true);
  ModeList::SetMode((ModeList *)this_00,1,0,false);
  ModeList::SetMode((ModeList *)this_00,2,0,false);
  ModeList::SetMode((ModeList *)this_00,3,0,false);
  ModeList::SetMode((ModeList *)this_00,4,0,false);
  ModeList::SetMode((ModeList *)this_00,5,0,false);
  ModeList::SetMode((ModeList *)this_00,6,0,false);
  ModeList::SetMode((ModeList *)this_00,7,0,false);
  ModeList::SetMode((ModeList *)this_00,8,0,false);
  ModeList::SetMode((ModeList *)this_00,9,0,false);
  ModeList::SetMode((ModeList *)this_00,10,0,false);
  return;
}
