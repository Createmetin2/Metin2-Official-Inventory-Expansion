	#Find
				"DayMode"				: self.__DayMode_Update,
	#Add
				"refreshinven"            : self.Update_inventory_ref,
				"update_envanter_lazim"   : self.Update_inventory_lazim,

#Add end of file
	if app.ENABLE_EXTEND_INVEN_SYSTEM:	
		def Update_inventory_ref(self):
			if self.interface:
				self.interface.SetInventoryPageKilit()
				
		def Update_inventory_lazim(self, lazim):
			self.wndPopupDialog = uiCommon.PopupDialog()
			self.wndPopupDialog.SetText(lazim + " " + localeInfo.ENVANTER_ANAH_LAZIM)
			self.wndPopupDialog.Open()