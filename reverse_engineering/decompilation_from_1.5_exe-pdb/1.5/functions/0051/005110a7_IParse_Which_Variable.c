/*
 * Entry: 005110a7
 * Name: IParse_Which_Variable
 * Namespace: Global
 * Signature: _variable_struct * IParse_Which_Variable(_domain * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_variable_struct * __cdecl IParse_Which_Variable(_domain *param_1,char *param_2)

{
  byte bVar1;
  _variable_struct *p_Var2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  p_Var2 = param_1->variables;
  do {
    if (p_Var2 == (_variable_struct *)0x0) {
      return (_variable_struct *)0x0;
    }
    pbVar3 = (byte *)p_Var2->variable_name;
    pbVar5 = (byte *)param_2;
    do {
      bVar1 = *pbVar5;
      bVar6 = bVar1 < *pbVar3;
      if (bVar1 != *pbVar3) {
LAB_005110d8:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_005110dd;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar6 = bVar1 < pbVar3[1];
      if (bVar1 != pbVar3[1]) goto LAB_005110d8;
      pbVar5 = pbVar5 + 2;
      pbVar3 = pbVar3 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_005110dd:
    if (iVar4 == 0) {
      return p_Var2;
    }
    p_Var2 = p_Var2->next_variable;
  } while( true );
}
