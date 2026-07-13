/*
 * Entry: 004b95ce
 * Name: Wingman::UpdateModeList
 * Namespace: Wingman
 * Signature: void UpdateModeList(Wingman * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Wingman::UpdateModeList(Wingman *this)

{
  undefined1 *this_00;
  
  HoverCraft::UpdateModeList((HoverCraft *)this);
  this_00 = &this->field_0x19c;
  ModeList::SetMode((ModeList *)this_00,7,0xd,true);
  ModeList::SetMode((ModeList *)this_00,8,0x10,true);
  ModeList::SetMode((ModeList *)this_00,9,0x11,true);
  return;
}
