#Find
			self.wndMoneySlot = self.GetChild("Money_Slot")

#Add
			if app.ENABLE_EXTEND_INVEN_SYSTEM:
				self.EX_INVEN_COVER_IMG_CLOSE = []
				self.EX_INVEN_COVER_IMG_OPEN = []
				for i in xrange(9):
					self.EX_INVEN_COVER_IMG_OPEN.append(self.GetChild("cover_open_" + str(i)))
					self.EX_INVEN_COVER_IMG_CLOSE.append(self.GetChild("cover_close_" + str(i)))

#Find
			if self.costumeButton and not app.ENABLE_COSTUME_SYSTEM:
				self.costumeButton.Hide()
				self.costumeButton.Destroy()
				self.costumeButton = 0

#Add
			if app.ENABLE_EXTEND_INVEN_SYSTEM:
				for i in xrange(9):
					self.EX_INVEN_COVER_IMG_CLOSE[i].Hide()
					self.EX_INVEN_COVER_IMG_OPEN[i].Hide()

#Find
		self.dlgPickMoney = dlgPickMoney
		
# Add
		if app.ENABLE_EXTEND_INVEN_SYSTEM:
			for i in xrange(9):
				self.EX_INVEN_COVER_IMG_OPEN[i].SetEvent(ui.__mem_func__(self.en_ac))
				
#Find
		self.mallButton = None
		
#Add
		if app.ENABLE_EXTEND_INVEN_SYSTEM:
			self.EX_INVEN_COVER_IMG_CLOSE = None
			self.EX_INVEN_COVER_IMG_OPEN = None

#Find
	def SetInventoryPage(self, page):
	
#Change like this
	if app.ENABLE_EXTEND_INVEN_SYSTEM:
		def UpdateInven(self):
			page = self.inventoryPageIndex
			for i in xrange(9):
				inv_plus = player.GetEnvanter() + i
				inv_pluss = player.GetEnvanter() - i
				if page == 2:
					if player.GetEnvanter() > 8:
						self.EX_INVEN_COVER_IMG_OPEN[i].Hide()
						self.EX_INVEN_COVER_IMG_CLOSE[i].Hide()
					else:
						self.EX_INVEN_COVER_IMG_OPEN[player.GetEnvanter()].Show()
						self.EX_INVEN_COVER_IMG_CLOSE[player.GetEnvanter()].Hide()
						if inv_pluss >= 0:
							self.EX_INVEN_COVER_IMG_OPEN[inv_pluss].Hide()
							self.EX_INVEN_COVER_IMG_CLOSE[inv_pluss].Hide()
						if inv_plus < 9:
							self.EX_INVEN_COVER_IMG_CLOSE[inv_plus].Show()
							self.EX_INVEN_COVER_IMG_OPEN[inv_plus].Hide()	
				elif page == 3:
					if player.GetEnvanter() < 9:	
						self.EX_INVEN_COVER_IMG_OPEN[i].Hide()
						self.EX_INVEN_COVER_IMG_CLOSE[i].Show()
					elif player.GetEnvanter() > 17:
						self.EX_INVEN_COVER_IMG_OPEN[i].Hide()
						self.EX_INVEN_COVER_IMG_CLOSE[i].Hide()
					else:
						self.EX_INVEN_COVER_IMG_OPEN[player.GetEnvanter()-9].Show()
						self.EX_INVEN_COVER_IMG_CLOSE[player.GetEnvanter()-9].Hide()
						if inv_pluss >= 0:
							self.EX_INVEN_COVER_IMG_OPEN[inv_pluss-9].Hide()
						if inv_plus < 18:
							self.EX_INVEN_COVER_IMG_CLOSE[inv_plus-9].Show()
				else:
					self.EX_INVEN_COVER_IMG_OPEN[i].Hide()
					self.EX_INVEN_COVER_IMG_CLOSE[i].Hide()
					
		def genislet(self):
			if uiPrivateShopBuilder.IsBuildingPrivateShop():
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.ENVANTER_UYARI)
				return
			net.Envanter_genislet()
			self.OnCloseQuestionDialog()
			
		def en_ac(self):
			needkeys = (2,2,2,2,3,3,4,4,4,5,5,5,6,6,6,7,7,7)
			self.questionDialog = uiCommon.QuestionDialog()
			self.questionDialog.SetText(localeInfo.ENVANTER_GENIS_1 % needkeys[player.GetEnvanter()])
			self.questionDialog.SetAcceptEvent(ui.__mem_func__(self.genislet))
			self.questionDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseQuestionDialog))
			self.questionDialog.Open()
	
	def SetInventoryPage(self, page):	
		self.inventoryPageIndex = page
		for index in range(len(self.inventoryTab)):
			if index == page:
				continue	
			self.inventoryTab[index].SetUp()
		if app.ENABLE_EXTEND_INVEN_SYSTEM:
			self.UpdateInven()			
		self.RefreshBagSlotWindow()
			
#Find
	def __UseItem(self, slotIndex):
		ItemVNum = player.GetItemIndex(slotIndex)
		item.SelectItem(ItemVNum)
		
#Add
		if app.ENABLE_EXTEND_INVEN_SYSTEM:
			if ItemVNum == 72320:
				self.en_ac()
