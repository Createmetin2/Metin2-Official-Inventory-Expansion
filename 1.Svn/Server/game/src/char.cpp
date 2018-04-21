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
				if (Envantertoplami > 18)
				{
					sys_err("[ENVANTER SINIRI HATASI]");
					return;
				}
				Set_Inventory_Point(Inven_Point() + amount);
				val = Inven_Point();
			}
			break;
#endif

///Add end of cpp
#ifdef ENABLE_EXTEND_INVEN_SYSTEM
static int NeedKeys[] = {2,2,2,2,3,3,4,4,4,5,5,5,6,6,6,7,7,7};
bool CHARACTER::Update_Inven()
{
	// #define key1 72319
	#define key2 72320
	int needkey = NeedKeys[Inven_Point()];
	
	if (CountSpecifyItem(key2) >= needkey)
		RemoveSpecifyItem(key2, needkey);
	else
	{
		int nekadar = needkey - CountSpecifyItem(key2);
		ChatPacket(CHAT_TYPE_COMMAND, "update_envanter_needkey %d", nekadar);
		return false;
	}
	PointChange(POINT_INVEN, 1, false);
	ChatPacket(CHAT_TYPE_COMMAND, "refreshinven");
	UpdatePacket();		
	return true;
}
#endif