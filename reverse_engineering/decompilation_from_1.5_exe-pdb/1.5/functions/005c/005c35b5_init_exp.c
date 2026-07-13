/*
 * Entry: 005c35b5
 * Name: init_exp
 * Namespace: Global
 * Signature: void init_exp(expdesc * param_1, expkind param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl init_exp(expdesc *param_1,expkind param_2,int param_3)

{
  undefined4 *in_EAX;
  undefined4 in_ECX;
  
  in_EAX[4] = 0xffffffff;
  in_EAX[5] = 0xffffffff;
  *in_EAX = in_ECX;
  in_EAX[2] = param_1;
  return;
}
