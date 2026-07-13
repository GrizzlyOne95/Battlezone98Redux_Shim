/*
 * Entry: 00552c81
 * Name: SaveDefaults
 * Namespace: Global
 * Signature: void SaveDefaults(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SaveDefaults(void)

{
  char cVar1;
  FILE *_File;
  int iVar2;
  
  _File = fopen("network.def","wb");
  if (_File != (FILE *)0x0) {
    iVar2 = 0;
    do {
      cVar1 = Net::hostname[iVar2];
      net_defaults.server[iVar2] = cVar1;
      iVar2 = iVar2 + 1;
    } while (cVar1 != '\0');
    fwrite(&net_defaults,0x278,1,_File);
    fclose(_File);
  }
  return;
}
