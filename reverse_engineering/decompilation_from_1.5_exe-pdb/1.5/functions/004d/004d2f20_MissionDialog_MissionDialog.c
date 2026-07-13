/*
 * Entry: 004d2f20
 * Name: MissionDialog::MissionDialog
 * Namespace: MissionDialog
 * Signature: MissionDialog * MissionDialog(MissionDialog * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MissionDialog * __thiscall MissionDialog::MissionDialog(MissionDialog *this)

{
  memset(this,0,0x58);
  (this->ofn).lStructSize = 0x58;
  (this->ofn).hwndOwner = Device.hwndApp;
  (this->ofn).hInstance = Device.hInstance;
  (this->ofn).nMaxFile = 0x104;
  return this;
}
