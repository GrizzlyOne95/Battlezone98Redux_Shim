/*
 * Entry: 00518efe
 * Name: stdext::_Unchecked_move_backward<GridPoint_*,GridPoint_*>
 * Namespace: stdext
 * Signature: GridPoint * _Unchecked_move_backward<GridPoint_*,GridPoint_*>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
stdext::_Unchecked_move_backward<GridPoint_*,GridPoint_*>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3)

{
  GridPoint *pGVar1;
  
  pGVar1 = std::
           _Move_backward_opt<GridPoint_*,GridPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                     (param_1,param_2,param_3,SUB41(param_2,0),(_Undefined_move_tag)SUB41(param_2,0)
                      ,(_Range_checked_iterator_tag)0x0);
  return pGVar1;
}
