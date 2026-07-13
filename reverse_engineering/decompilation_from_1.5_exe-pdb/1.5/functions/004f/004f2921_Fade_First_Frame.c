/*
 * Entry: 004f2921
 * Name: Fade_First_Frame
 * Namespace: Global
 * Signature: void Fade_First_Frame(float param_1, long param_2, long param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Fade_First_Frame(float param_1,long param_2,long param_3,long param_4,long param_5)

{
  Fade_First_Frame_Cueing_Flag = 1;
  Fade_Frame(0,param_1,param_2,param_3,param_4,param_5);
  return;
}
