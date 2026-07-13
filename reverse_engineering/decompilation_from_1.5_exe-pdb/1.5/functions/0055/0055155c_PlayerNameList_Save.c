/*
 * Entry: 0055155c
 * Name: PlayerNameList::Save
 * Namespace: PlayerNameList
 * Signature: void Save(PlayerNameList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::Save(PlayerNameList *this,char *param_1)

{
  FILE *_File;
  char *pcVar1;
  int local_4;
  
  if ((param_1 != (char *)0x0) && (_File = fopen(param_1,"w"), _File != (FILE *)0x0)) {
    local_4 = 0;
    if (0 < this->count) {
      do {
        fprintf(_File,"%s\n",this->name[local_4]);
        fprintf(_File,"%s\n",this->email[local_4]);
        fprintf(_File,"%s\n",this->url[local_4]);
        fprintf(_File,"%s\n",this->flag[local_4]);
        for (pcVar1 = this->description[local_4]; *pcVar1 != '\0'; pcVar1 = pcVar1 + 1) {
          if (*pcVar1 == '\n') {
            *pcVar1 = '_';
          }
        }
        fprintf(_File,"%s\n",this->description[local_4]);
        for (pcVar1 = this->description[local_4]; *pcVar1 != '\0'; pcVar1 = pcVar1 + 1) {
          if (*pcVar1 == '_') {
            *pcVar1 = '\n';
          }
        }
        local_4 = local_4 + 1;
      } while (local_4 < this->count);
    }
    fclose(_File);
  }
  return;
}
