/*
 * Entry: 005c71c1
 * Name: pre_cpp_init
 * Namespace: Global
 * Signature: void pre_cpp_init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl pre_cpp_init(void)

{
  atexit(_RTC_Terminate);
  startinfo.newmode = _newmode;
  argret = __getmainargs(&argc,&argv,&envp,_dowildcard,(_startupinfo *)&startinfo);
  if (argret < 0) {
    amsg_exit(8);
  }
  return;
}
