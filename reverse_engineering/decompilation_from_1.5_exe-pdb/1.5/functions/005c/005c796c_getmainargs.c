/*
 * Entry: 005c796c
 * Name: ___getmainargs
 * Namespace: Global
 * Signature: int ___getmainargs(int * _Argc, char * * * _Argv, char * * * _Env, int _DoWildCard, _startupinfo * _StartInfo)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
___getmainargs(int *_Argc,char ***_Argv,char ***_Env,int _DoWildCard,_startupinfo *_StartInfo)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c796c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = __getmainargs(_Argc,_Argv,_Env,_DoWildCard,_StartInfo);
  return iVar1;
}
