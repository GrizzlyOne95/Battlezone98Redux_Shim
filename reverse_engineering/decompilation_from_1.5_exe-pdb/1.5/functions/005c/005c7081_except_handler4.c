/*
 * Entry: 005c7081
 * Name: _except_handler4
 * Namespace: Global
 * Signature: _EXCEPTION_DISPOSITION _except_handler4(_EXCEPTION_RECORD * param_1, _EXCEPTION_REGISTRATION_RECORD * param_2, _CONTEXT * param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_EXCEPTION_DISPOSITION __cdecl
_except_handler4(_EXCEPTION_RECORD *param_1,_EXCEPTION_REGISTRATION_RECORD *param_2,
                _CONTEXT *param_3,void *param_4)

{
  _EXCEPTION_DISPOSITION _Var1;
  
  _Var1 = except_handler4_common
                    (&__security_cookie,__security_check_cookie,param_1,param_2,param_3,param_4);
  return _Var1;
}
