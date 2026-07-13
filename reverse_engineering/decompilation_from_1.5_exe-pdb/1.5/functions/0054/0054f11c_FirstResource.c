/*
 * Entry: 0054f11c
 * Name: FirstResource
 * Namespace: Global
 * Signature: int FirstResource(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl FirstResource(void)

{
  FILE *_File;
  char *pcVar1;
  int iVar2;
  
  GetCDDrives();
  FindCDByName("BZONE",1);
  InitCache();
  zfsMemoryInit();
  _File = fopen("xyzzy","rb");
  if (_File != (FILE *)0x0) {
    fclose(_File);
  }
  zixCDMode = (int)(_File == (FILE *)0x0);
  zixGetVolumeName = GetVolumeName;
  zixGetCDDrive = CDDriveLetter;
  zixAskForNewCD = AskForNewCD;
  if ((useD3D & 1U) == 0) {
    pcVar1 = "bzone.zix";
  }
  else if ((useD3D & 2U) == 0) {
    if ((useD3D & 0xfffffff8U) == 0) {
      pcVar1 = "bzone8s.zix";
    }
    else {
      pcVar1 = "bzone8l.zix";
    }
  }
  else if (useD3D >> 3 == 0) {
    pcVar1 = "bzone16s.zix";
  }
  else if (useD3D >> 3 == 2) {
    pcVar1 = "bzone16q.zix";
  }
  else {
    pcVar1 = "bzone16l.zix";
  }
  iVar2 = zixBuildIndex(pcVar1);
  if (iVar2 != 0) {
    return 1;
  }
  pcVar1 = (char *)_StrLookupFind(_DAT_00224566,
                                  "Sorry, unable to find required files to run. Please check your working directory or reinstall the game."
                                 );
                    /* WARNING: Subroutine does not return */
  I76FatalError(pcVar1);
}
