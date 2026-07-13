/*
 * Entry: 005c7b30
 * Name: _invoke_watson_if_error
 * Namespace: Global
 * Signature: void _invoke_watson_if_error(int param_1, wchar_t * param_2, wchar_t * param_3, wchar_t * param_4, uint param_5, uint param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_invoke_watson_if_error
          (int param_1,wchar_t *param_2,wchar_t *param_3,wchar_t *param_4,uint param_5,uint param_6)

{
  if (param_1 != 0) {
    invoke_watson(param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}
