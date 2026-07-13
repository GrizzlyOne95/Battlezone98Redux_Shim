/*
 * Entry: 0051736e
 * Name: ScheduleGlue_Translate_Pos_To_Tiles
 * Namespace: Global
 * Signature: void ScheduleGlue_Translate_Pos_To_Tiles(VECTOR_3D param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScheduleGlue_Translate_Pos_To_Tiles(VECTOR_3D param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = PosX2POS((double)param_1.x);
  *param_2 = iVar1;
  iVar1 = PosZ2POS((double)param_1.z);
  *param_3 = iVar1;
  return;
}
