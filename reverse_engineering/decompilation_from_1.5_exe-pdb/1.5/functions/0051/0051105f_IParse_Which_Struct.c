/*
 * Entry: 0051105f
 * Name: IParse_Which_Struct
 * Namespace: Global
 * Signature: _struct_list_element * IParse_Which_Struct(_domain * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_struct_list_element * __cdecl IParse_Which_Struct(_domain *param_1,char *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  
  do {
    param_1 = (_domain *)param_1->the_structs;
    if (param_1 == (_domain *)0x0) {
      return (_struct_list_element *)0x0;
    }
    pbVar2 = (byte *)param_1->number_of_variables;
    pbVar4 = (byte *)param_2;
    do {
      bVar1 = *pbVar4;
      bVar5 = bVar1 < *pbVar2;
      if (bVar1 != *pbVar2) {
LAB_0051108f:
        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_00511094;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar5 = bVar1 < pbVar2[1];
      if (bVar1 != pbVar2[1]) goto LAB_0051108f;
      pbVar4 = pbVar4 + 2;
      pbVar2 = pbVar2 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00511094:
    if (iVar3 == 0) {
      return (_struct_list_element *)param_1;
    }
  } while( true );
}
