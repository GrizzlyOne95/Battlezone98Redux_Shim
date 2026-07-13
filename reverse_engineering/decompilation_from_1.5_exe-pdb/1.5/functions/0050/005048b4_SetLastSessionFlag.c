/*
 * Entry: 005048b4
 * Name: SetLastSessionFlag
 * Namespace: Global
 * Signature: int SetLastSessionFlag(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetLastSessionFlag(void)

{
  uchar uVar1;
  FILE *_File;
  size_t sVar2;
  
  if (SessionFlags.newHWSW != '\0') {
    if (SessionFlags.newHWSW == 0xf0) {
      (UserProfilePtr->graphicDetail).hardware = '\x01';
      (UserProfilePtr->graphicDetail).resolution = SessionFlags.newRes;
      (UserProfilePtr->graphicDetail).resolution = '\b';
    }
    else {
      (UserProfilePtr->graphicDetail).hardware = '\0';
      (UserProfilePtr->graphicDetail).resolution = SessionFlags.newRes;
      uVar1 = (UserProfilePtr->graphicDetail).resolution;
      if (((uVar1 != '\x05') && (uVar1 != '\x06')) && (uVar1 != '\a')) {
        (UserProfilePtr->graphicDetail).resolution = '\x05';
      }
    }
    SaveUserProfile();
  }
  SessionFlags.signature[0] = 'B';
  SessionFlags.signature[1] = 'Z';
  SessionFlags.state = 0xaa;
  SessionFlags.newHWSW = '\0';
  SessionFlags.oldMode = (UserProfilePtr->graphicDetail).hardware;
  SessionFlags.oldRes = (UserProfilePtr->graphicDetail).resolution;
  _File = fopen(SessionFlagsFileName,"wbc");
  if (_File != (FILE *)0x0) {
    sVar2 = fwrite(&SessionFlags,8,1,_File);
    if (sVar2 == 1) goto LAB_00504983;
  }
  DEBUG_systemError(grOptErrorMsg);
LAB_00504983:
  fflush(_File);
  fclose(_File);
  return 1;
}
