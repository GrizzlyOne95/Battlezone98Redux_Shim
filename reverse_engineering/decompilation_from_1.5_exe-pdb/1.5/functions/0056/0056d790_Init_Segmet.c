/*
 * Entry: 0056d790
 * Name: Init_Segmet
 * Namespace: Global
 * Signature: void Init_Segmet(float param_1, long param_2, AiPath * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Segmet(float param_1,long param_2,AiPath *param_3)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  int in_ECX;
  
  pfVar1 = (float *)(*(int *)(in_ECX + 8) + in_EAX * 8);
  fVar2 = pfVar1[2] - *pfVar1;
  fVar3 = pfVar1[3] - pfVar1[1];
  Camera_Record.l = (double)param_1;
  Camera_Record.xt = (double)(param_1 * fVar2 + *pfVar1);
  Camera_Record.zt = (double)(param_1 * fVar3 + pfVar1[1]);
  Camera_Record.dx = (double)fVar2;
  Camera_Record.dz = (double)fVar3;
  Camera_Record.segment = in_EAX;
  Camera_Record.dl = rsqrt((double)(fVar3 * fVar3 + fVar2 * fVar2));
  return;
}
