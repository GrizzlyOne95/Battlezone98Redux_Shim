/*
 * Entry: 004b2d85
 * Name: TexAnim_RegOneShot
 * Namespace: Global
 * Signature: void TexAnim_RegOneShot(_OBJ76 * param_1, char * param_2, float param_3, long param_4, long param_5, _func___cdecl_void__OBJ76_ptr * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
TexAnim_RegOneShot(_OBJ76 *param_1,char *param_2,float param_3,long param_4,long param_5,
                  _func___cdecl_void__OBJ76_ptr *param_6)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  
  pfVar1 = operator_new(0x1c);
  fVar3 = Get_TimeLocal();
  pfVar1[3] = 0.0;
  *pfVar1 = fVar3 + param_3;
  pfVar1[2] = (float)param_5;
  pfVar1[1] = param_3;
  pfVar1[4] = (float)param_4;
  pfVar1[5] = 2.8026e-45;
  pfVar1[6] = (float)param_6;
  iVar2 = TexAnim_Register(param_1,param_2,loopanim_cb,pfVar1);
  if (iVar2 != 0) {
    Texture_Select(param_1,param_2,1,(long)pfVar1[4],0);
    Texture_Select(param_1,param_2,0,(long)pfVar1[3],1);
  }
  return;
}
