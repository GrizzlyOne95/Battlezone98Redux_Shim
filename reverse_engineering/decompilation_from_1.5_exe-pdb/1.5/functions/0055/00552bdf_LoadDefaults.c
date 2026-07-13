/*
 * Entry: 00552bdf
 * Name: LoadDefaults
 * Namespace: Global
 * Signature: void LoadDefaults(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LoadDefaults(void)

{
  FILE *_File;
  size_t sVar1;
  
  _File = fopen("network.def","rb");
  if (_File != (FILE *)0x0) {
    sVar1 = fread(&net_defaults,0x278,1,_File);
    fclose(_File);
    if (sVar1 == 1) {
      return;
    }
  }
  net_defaults.modeminitstring[0] = '\0';
  net_defaults.modemcomport = 0;
  net_defaults.serialcomport = 0;
  net_defaults.baud = 0xe100;
  net_defaults.TransportIndex = 1;
  net_defaults.deathmatch = true;
  net_defaults.password[0] = '\0';
  builtin_strncpy(net_defaults.gamename,"gamename",9);
  builtin_strncpy(net_defaults.playercraft,"avtank",7);
  builtin_strncpy(net_defaults.playername,"playername",0xb);
  return;
}
