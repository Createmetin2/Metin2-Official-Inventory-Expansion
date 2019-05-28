//Find
bool CExchange::CheckSpace()
{
	....
	....
}
///Change
bool CExchange::CheckSpace()
{	
	constexpr int INVEN_NUM_SLOT = 5*9;
	std::array<CGrid*, static_cast<const int>(INVENTORY_MAX_NUM / INVEN_NUM_SLOT)> s_grid;
	static std::vector <WORD> s_vDSGrid(DRAGON_SOUL_INVENTORY_MAX_NUM);
    LPITEM item;
	bool bDSInitialized, existspace = false;
    int new_size, default_open_inven = 2, invenpoint = GetCompany()->GetOwner()->Inven_Point();
	
	for (size_t i = 0; i < s_grid.size(); i++)
    {
        if (i < default_open_inven) {
            s_grid[i] = new CGrid(5,9);
            continue;
        }
        if (invenpoint > 0 && invenpoint <= 9)
            new_size = invenpoint;
        else if (invenpoint >= 9)
            new_size = 9;
        else
            new_size = 0;
        s_grid[i] = new CGrid(5,new_size);
        invenpoint-=9;
    }
   for (size_t j = 0; j < s_grid.size(); j++) {
        s_grid[j]->Clear();
        for (auto i = INVEN_NUM_SLOT * j; i < INVEN_NUM_SLOT * (j+1); ++i) {
    		if (!(item = GetCompany()->GetOwner()->GetInventoryItem(i))) 
    		    continue;
    		s_grid[j]->Put(i - INVEN_NUM_SLOT * j, 1, item->GetSize());
		}
	}
    for (auto i = 0; i < EXCHANGE_ITEM_MAX_NUM; ++i) {
        if (!(item = m_apItems[i])) continue;
        if (item->IsDragonSoul()) {
            if (!GetCompany()->GetOwner()->DragonSoul_IsQualified()) return false;
            if (!bDSInitialized) {
                bDSInitialized = true;
                GetCompany()->GetOwner()->CopyDragonSoulItemGrid(s_vDSGrid);
            }
            bool bExistEmptySpace = false;
            WORD wBasePos = DSManager::instance().GetBasePosition(item);		
            if (wBasePos >= DRAGON_SOUL_INVENTORY_MAX_NUM) return false;
            for (int i = 0; i < DRAGON_SOUL_BOX_SIZE; i++) {
                WORD wPos = wBasePos + i;
                if (0 == s_vDSGrid[wBasePos]) {
                    bool bEmpty = true;
                    for (int j = 1; j < item->GetSize(); j++)	{
                        if (s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM]) {
                            bEmpty = false;
                            break;
                    }} if (bEmpty)	{
                        for (int j = 0; j < item->GetSize(); j++)
                            s_vDSGrid[wPos + j * DRAGON_SOUL_BOX_COLUMN_NUM] =  wPos + 1;
                        bExistEmptySpace = true;
                        break;
                    }} if (bExistEmptySpace) break;
            } if (!bExistEmptySpace) return false;
        }
		else {
			for (auto i = 0; i < s_grid.size(); i++) {
				int iPos = s_grid[i]->FindBlank(1, item->GetSize());
				if (iPos >= 0) {
					s_grid[i]->Put(iPos, 1, item->GetSize());
					existspace = true;
					break;
			}} if (!existspace) return false;
		}}
	return true;
}