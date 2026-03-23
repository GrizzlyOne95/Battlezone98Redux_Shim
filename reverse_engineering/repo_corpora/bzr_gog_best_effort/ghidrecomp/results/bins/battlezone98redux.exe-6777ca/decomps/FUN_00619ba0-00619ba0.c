
void FUN_00619ba0(char *param_1)

{
  if (param_1 == (LPCSTR)0x0) {
    param_1 = 
    "Sorry, there is not enough memory to continue.\nPlease make sure that you have at least 50MB free on your hard drive and that virtual memory is not disabled."
    ;
  }
  FUN_00618530();
  MessageBoxA((HWND)*DAT_02cecefc,param_1,"Battlezone 98 Redux",0x10);
                    /* WARNING: Subroutine does not return */
  exit(0x6b);
}

