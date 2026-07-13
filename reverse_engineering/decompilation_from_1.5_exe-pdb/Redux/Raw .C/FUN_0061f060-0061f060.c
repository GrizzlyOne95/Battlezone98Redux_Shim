
void FUN_0061f060(void)

{
  FILE *_File;
  FILE *_File_00;
  int iVar1;
  char local_310 [260];
  char local_20c [256];
  char local_10c [260];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_310,"%s%s%s",&DAT_02cf2000,&DAT_00871328,"temp.map");
  sprintf(local_10c,"%s%s%s",&DAT_02cf2000,&DAT_00871328,"input.map");
  _chmod(local_10c,0x80);
  _File = fopen(local_10c,"w");
  _File_00 = fopen(local_310,"r");
  while (iVar1 = FUN_0061e530(local_20c,0xff,_File_00), iVar1 != 0) {
    fprintf(_File,"%s\n",local_20c);
    if (local_20c[0] == '}') {
      fprintf(_File,"\n");
    }
  }
  fclose(_File_00);
  fclose(_File);
  _chmod(local_10c,0x100);
  FUN_0083e885();
  return;
}

