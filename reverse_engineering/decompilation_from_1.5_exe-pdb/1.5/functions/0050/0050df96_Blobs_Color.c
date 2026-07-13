/*
 * Entry: 0050df96
 * Name: Blobs_Color
 * Namespace: Global
 * Signature: void Blobs_Color(ushort * * param_1, int param_2, int param_3, ushort param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x0050dfc8) */
/* WARNING: Removing unreachable block (ram,0x0050dfdd) */
/* WARNING: Removing unreachable block (ram,0x0050e008) */
/* WARNING: Removing unreachable block (ram,0x0050e020) */
/* WARNING: Removing unreachable block (ram,0x0050e032) */
/* WARNING: Removing unreachable block (ram,0x0050e035) */
/* WARNING: Removing unreachable block (ram,0x0050e03d) */
/* WARNING: Removing unreachable block (ram,0x0050e053) */
/* WARNING: Removing unreachable block (ram,0x0050e068) */
/* WARNING: Removing unreachable block (ram,0x0050e071) */
/* WARNING: Removing unreachable block (ram,0x0050e083) */
/* WARNING: Removing unreachable block (ram,0x0050e098) */
/* WARNING: Removing unreachable block (ram,0x0050e0a0) */
/* WARNING: Removing unreachable block (ram,0x0050e0b3) */
/* WARNING: Removing unreachable block (ram,0x0050e0c5) */

void __cdecl
Blobs_Color(ushort **param_1,int param_2,int param_3,ushort param_4,int param_5,int param_6)

{
  int unaff_EBX;
  int unaff_ESI;
  _coloring_point **unaff_EDI;
  int in_stack_ffffffe4;
  
  Blobs_Add_Point_To_Grow_List
            ((ushort **)(uint)param_4,unaff_EDI,unaff_ESI,unaff_EBX,in_stack_ffffffe4);
  return;
}
