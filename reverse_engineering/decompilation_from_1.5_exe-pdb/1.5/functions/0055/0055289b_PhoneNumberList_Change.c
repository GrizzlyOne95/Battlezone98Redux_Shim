/*
 * Entry: 0055289b
 * Name: PhoneNumberList::Change
 * Namespace: PhoneNumberList
 * Signature: void Change(PhoneNumberList * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Change(PhoneNumberList *this,char *param_1,char *param_2)

{
  if (this->edit != false) {
    Delete(this);
  }
  Add(this,param_1,param_2);
  return;
}
