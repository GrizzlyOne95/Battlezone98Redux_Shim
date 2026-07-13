/*
 * Entry: 00552603
 * Name: PhoneNumberList::GetNumber
 * Namespace: PhoneNumberList
 * Signature: char * GetNumber(PhoneNumberList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall PhoneNumberList::GetNumber(PhoneNumberList *this,int param_1)

{
  char *pcVar1;
  
  if ((param_1 < 0) || (this->count <= param_1)) {
    pcVar1 = "";
  }
  else {
    pcVar1 = this->number[param_1];
  }
  return pcVar1;
}
