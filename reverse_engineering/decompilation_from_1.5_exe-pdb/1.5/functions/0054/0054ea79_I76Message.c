/*
 * Entry: 0054ea79
 * Name: I76Message
 * Namespace: Global
 * Signature: int I76Message(char * param_1, int param_2, int param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl I76Message(char *param_1,int param_2,int param_3,char *param_4)

{
  long lVar1;
  int iVar2;
  long unaff_ESI;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  OverlayDefaultPalette(0,0x100,0);
  UnlockMouse();
  _vsnprintf(local_408,0x400,param_4,&stack0x00000014);
  lVar1 = I76MessageBox(local_408,(char *)(uint)(param_2 != 0),unaff_ESI);
  if ((lVar1 == 2) || (param_2 == 0)) {
    if (param_3 != 0) {
      LastInputs();
                    /* WARNING: Subroutine does not return */
      exit(0x73);
    }
    iVar2 = 0;
  }
  else {
    LockMouse();
    iVar2 = 1;
  }
  return iVar2;
}
