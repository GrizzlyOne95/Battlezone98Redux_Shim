
void __fastcall FUN_0065f0c0(int param_1)

{
  FILE *_File;
  
  *(undefined4 *)(param_1 + 800) = 1;
  *(undefined4 *)(param_1 + 0x554) = 0;
  *(undefined4 *)(param_1 + 0x570) = 0;
  *(undefined4 *)(param_1 + 0x56c) = 0;
  *(undefined4 *)(param_1 + 0x568) = 0;
  _File = fopen("emission.bst","rb");
  if (_File != (FILE *)0x0) {
    fread((void *)(param_1 + 0x568),4,1,_File);
    *(undefined4 *)(param_1 + 0x56c) = *(undefined4 *)(param_1 + 0x568);
    fread((void *)(param_1 + 0x570),4,1,_File);
    fclose(_File);
  }
  return;
}

