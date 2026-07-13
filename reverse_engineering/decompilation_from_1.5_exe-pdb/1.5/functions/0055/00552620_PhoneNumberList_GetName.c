/*
 * Entry: 00552620
 * Name: PhoneNumberList::GetName
 * Namespace: PhoneNumberList
 * Signature: char * GetName(PhoneNumberList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall PhoneNumberList::GetName(PhoneNumberList *this,int param_1)

{
  char *pcVar1;
  
  if ((param_1 < 0) || (this->count <= param_1)) {
    pcVar1 = "";
  }
  else {
    pcVar1 = this->name[param_1];
  }
  return pcVar1;
}
