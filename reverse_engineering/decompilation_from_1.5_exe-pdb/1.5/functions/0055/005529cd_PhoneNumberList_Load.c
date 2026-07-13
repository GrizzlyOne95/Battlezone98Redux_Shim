/*
 * Entry: 005529cd
 * Name: PhoneNumberList::Load
 * Namespace: PhoneNumberList
 * Signature: void Load(PhoneNumberList * this, HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Load(PhoneNumberList *this,HWND__ *param_1)

{
  this->hwnd = param_1;
  Load(this,"netpho.txt");
  return;
}
