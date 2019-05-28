//Find
	tab.skill_group	= m_points.skill_group;
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	tab.envanter 		= Inven_Point();
#endif

//Find
	pack.points[POINT_MAX_STAMINA] = GetMaxStamina();
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	pack.points[POINT_INVEN]		= Inven_Point();
#endif

//Find
	SetGold(t->gold);
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	Set_Inventory_Point(t->envanter);
#endif

//Find
	long lSPRecovery = GetPoint(POINT_SP_RECOVERY);

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	long envanterim = Inven_Point();
#endif

//Find
	SetPoint(POINT_PC_BANG_DROP_BONUS, 0);

///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
	SetPoint(POINT_INVEN, envanterim);
#endif

//Find
		case POINT_MAX_STAMINA:
			SetMaxStamina(GetMaxStamina() + amount);
			val = GetMaxStamina();
			break;
	
///Add
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
		case POINT_INVEN:
			{
				const int64_t Envantertoplami = static_cast<int64_t>(Inven_Point()) + static_cast<int64_t>(amount);
				int inven_count = INVENTORY_MAX_NUM / (9*5), default_open_inven = 2;
				if (Envantertoplami > (inven_count-default_open_inven)*9)
				{
					sys_err("[POINT_INVEN ERROR]");
					return;
				}
				Set_Inventory_Point(Inven_Point() + amount);
				val = Inven_Point();
			}
			break;
#endif

///Add end of cpp
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
bool CHARACTER::Update_Inven()
{
	std::vector<int> needkeys;
	int key = 72320, inven_count = INVENTORY_MAX_NUM / (9*5), default_open_inven = 2;
	int envanter = inven_count-default_open_inven;
	for (auto i = 2; i <= (envanter*3)+1; i++)
		for (auto j = 0; j < 3; j++)
			needkeys.push_back(i);
		
	int needkey = needkeys[Inven_Point()];
	if (CountSpecifyItem(key) >= needkey)
		RemoveSpecifyItem(key, needkey);
	else
	{
		int nekadar = needkey - CountSpecifyItem(key);
		ChatPacket(CHAT_TYPE_COMMAND, "update_envanter_lazim %d", nekadar);
		return false;
	}
	PointChange(POINT_INVEN, 1, false);
	ChatPacket(CHAT_TYPE_COMMAND, "refreshinven");
	UpdatePacket();		
	return true;
}
#endif
