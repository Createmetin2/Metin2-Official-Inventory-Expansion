#Find
	def RefreshInventory(self):
		self.wndTaskBar.RefreshQuickSlot()
		self.wndInventory.RefreshItemSlot()
		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			self.wndDragonSoul.RefreshItemSlot()
			
#Add
	if app.ENABLE_EXTEND_INVEN_SYSTEM:
		def SetInventoryPageKilit(self):
			self.wndInventory.UpdateInven()