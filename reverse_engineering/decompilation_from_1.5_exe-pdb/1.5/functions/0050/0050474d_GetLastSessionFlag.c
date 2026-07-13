/*
 * Entry: 0050474d
 * Name: GetLastSessionFlag
 * Namespace: Global
 * Signature: int GetLastSessionFlag(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetLastSessionFlag(void)

{
  FILE *_File;
  size_t sVar1;
  int iVar2;
  uint uVar3;
  
  _File = fopen(SessionFlagsFileName,"r+bc");
  if (_File == (FILE *)0x0) {
    _File = fopen(SessionFlagsFileName,"w+bc");
    if (_File == (FILE *)0x0) {
      DEBUG_systemError(grOptErrorMsg);
                    /* WARNING: Subroutine does not return */
      exit(-1);
    }
  }
  sVar1 = fread(&SessionFlags,8,1,_File);
  if (sVar1 == 1) {
    uVar3 = (uint)(SessionFlags.state == 0xaa);
  }
  else {
    uVar3 = 0;
  }
  SessionFlags.signature[0] = 'B';
  SessionFlags.signature[1] = 'Z';
  SessionFlags.state = 'U';
  SessionFlags.newHWSW = '\0';
  rewind(_File);
  sVar1 = fwrite(&SessionFlags,8,1,_File);
  if (sVar1 != 1) {
    DEBUG_systemError(grOptErrorMsg);
  }
  fflush(_File);
  fclose(_File);
  if (useD3D == 0) {
    if ((uVar3 == 0) && ((UserProfilePtr->graphicDetail).hardware != '\0')) {
      iVar2 = do_warning();
      if (iVar2 != 0) {
        (UserProfilePtr->graphicDetail).hardware = '\0';
      }
      if (useD3D != 0) goto LAB_0050483e;
    }
    (UserProfilePtr->graphicDetail).hardware = '\0';
  }
  else {
LAB_0050483e:
    (UserProfilePtr->graphicDetail).hardware = '\x01';
  }
  if ((UserProfilePtr->graphicDetail).hardware == '\0') {
    useD3D = 0;
    if (((uVar3 == 0) && ((UserProfilePtr->graphicDetail).resolution != '\x05')) ||
       (7 < (UserProfilePtr->graphicDetail).resolution)) {
      (UserProfilePtr->graphicDetail).resolution = '\x05';
    }
  }
  else {
    useD3D = 1;
    if (((uVar3 == 0) && ((UserProfilePtr->graphicDetail).resolution != '\b')) ||
       ((UserProfilePtr->graphicDetail).resolution < 8)) {
      (UserProfilePtr->graphicDetail).resolution = '\b';
    }
  }
  SaveUserProfile();
  SessionFlags.oldMode = (UserProfilePtr->graphicDetail).hardware;
  SessionFlags.oldRes = (UserProfilePtr->graphicDetail).resolution;
  return uVar3;
}
