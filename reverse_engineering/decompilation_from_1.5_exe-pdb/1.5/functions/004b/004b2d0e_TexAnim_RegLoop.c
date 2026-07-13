/*
 * Entry: 004b2d0e
 * Name: TexAnim_RegLoop
 * Namespace: Global
 * Signature: void TexAnim_RegLoop(_OBJ76 * param_1, char * param_2, float param_3, long param_4, long param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
TexAnim_RegLoop(_OBJ76 *param_1,char *param_2,float param_3,long param_4,long param_5,int param_6)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = operator_new(0x1c);
  fVar2 = Get_TimeLocal();
  pfVar1[2] = (float)param_5;
  *pfVar1 = fVar2 + param_3;
  pfVar1[4] = (float)param_4;
  pfVar1[1] = param_3;
  pfVar1[3] = 0.0;
  pfVar1[6] = 0.0;
  pfVar1[5] = (float)(uint)(param_6 == 0);
  TexAnim_Register(param_1,param_2,loopanim_cb,pfVar1);
  Texture_Select(param_1,param_2,1,(long)pfVar1[4],0);
  Texture_Select(param_1,param_2,0,(long)pfVar1[3],1);
  return;
}
