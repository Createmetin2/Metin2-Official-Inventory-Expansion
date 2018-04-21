//Find
bool CExchange::CheckSpace()
{
	....
	....
	....
}
///Change
bool CExchange::CheckSpace()
{
	CGrid * s_grid1 = new CGrid(5,9); CGrid * s_grid2 = new CGrid(5,9); CGrid * s_grid3; CGrid * s_grid4;
	
    LPCHARACTER victim = GetCompany()->GetOwner();
    LPITEM item; int i; int gridsize = victim->Inven_Point(); int INVEN_NUM_SLOT = 45;
	
	if (gridsize >= 9) {gridsize -= 9;s_grid3 = new CGrid(5,9);s_grid4 = new CGrid(5,gridsize);}
	else {s_grid3 = new CGrid(5,gridsize); s_grid4 = new CGrid(5,0);}
	
	s_grid1->Clear(); s_grid2->Clear(); s_grid3->Clear(); s_grid4->Clear();
	
	for (i = 0; i < INVEN_NUM_SLOT; ++i)	{
		if (!(item = victim->GetInventoryItem(i))) continue;
		s_grid1->Put(i, 1, item->GetSize());
	}
	for (i = INVEN_NUM_SLOT; i < INVEN_NUM_SLOT * 2; ++i)	{
		if (!(item = victim->GetInventoryItem(i))) continue;
		s_grid2->Put(i - INVEN_NUM_SLOT, 1, item->GetSize());
	}
	for (i = INVEN_NUM_SLOT * 2; i < INVEN_NUM_SLOT * 3; ++i)	{
		if (!(item = victim->GetInventoryItem(i))) continue;

		s_grid3->Put(i - INVEN_NUM_SLOT * 2, 1, item->GetSize());
	}
	for (i = INVEN_NUM_SLOT * 3; i < INVEN_NUM_SLOT * 4; ++i)	{
		if (!(item = victim->GetInventoryItem(i))) continue;
		s_grid4->Put(i - INVEN_NUM_SLOT * 3, 1, item->GetSize());
	}
 
    static std::vector <WORD> s_vDSGrid(DRAGON_SOUL_INVENTORY_MAX_NUM);  
    bool bDSInitialized = false;
     
    for (i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i)	{
        if (!(item = m_apItems[i]))
			continue;
        if (item->IsDragonSoul())	{
            if (!victim->DragonSoul_IsQualified())
                return false;
 
            if (!bDSInitialized)	{
                bDSInitialized = true;
                victim->CopyDragonSoulItemGrid(s_vDSGrid);
            }
 
            bool bExistEmptySpace = false;
            WORD wBasePos = DSManager::instance().GetBasePosition(item);
			
            if (wBasePos >= DRAGON_SOUL_INVENTORY_MAX_NUM)
                return false;
             
            for (int i = 0; i < DRAGON_SOUL_BOX_SIZE; i++)	{
                WORD wPos = wBasePos + i;
                if (0 == s_vDSGrid[wBasePos])	{
                    bool bEmpty = true;
                    for (int j = 1; j < item->GetSize(); j++)	{
                        if (s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM])	{
                            bEmpty = false;
                            break;
                        }
                    }
                    if (bEmpty)	{
                        for (int j = 0; j < item->GetSize(); j++)
                            s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM] =  wPos + 1;
						
                        bExistEmptySpace = true;
                        break;
                    }
                }
                if (bExistEmptySpace) break;
            }
            if (!bExistEmptySpace) return false;
        }
		else
		{
			int iPos = s_grid1->FindBlank(1, item->GetSize());
			if (iPos >= 0)
				s_grid1->Put(iPos, 1, item->GetSize());
			else	{
				iPos = s_grid2->FindBlank(1, item->GetSize());
				if (iPos >= 0)
					s_grid2->Put(iPos, 1, item->GetSize());
				else	{
					iPos = s_grid3->FindBlank(1, item->GetSize());
					if (iPos >= 0)
						s_grid3->Put(iPos, 1, item->GetSize());
					else	{
						iPos = s_grid4->FindBlank(1, item->GetSize());
						if (iPos >= 0)
							s_grid4->Put(iPos, 1, item->GetSize());
						else
							return false;
					}
				}
			}
		}
	}
	return true;
}