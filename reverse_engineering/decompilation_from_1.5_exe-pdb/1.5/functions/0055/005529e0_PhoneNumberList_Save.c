/*
 * Entry: 005529e0
 * Name: PhoneNumberList::Save
 * Namespace: PhoneNumberList
 * Signature: void Save(PhoneNumberList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Save(PhoneNumberList *this,char *param_1)

{
  FILE *_File;
  int iVar1;
  
  iVar1 = 0;
  if ((param_1 != (char *)0x0) && (_File = fopen(param_1,"w"), _File != (FILE *)0x0)) {
    if (0 < this->count) {
      do {
        fprintf(_File,"%s\n",this->name[iVar1]);
        fprintf(_File,"%s\n",this->number[iVar1]);
        iVar1 = iVar1 + 1;
      } while (iVar1 < this->count);
    }
    fclose(_File);
  }
  return;
}
