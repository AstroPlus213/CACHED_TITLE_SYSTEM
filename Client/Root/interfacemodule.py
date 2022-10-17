
if app.ENABLE_TITLE_SYSTEM:
	import uiTitleWindow

##############################

		self.wndGuildBuilding = None
		if app.ENABLE_TITLE_SYSTEM:
			self.wndTitle = None
		self.listGMName = {}

##############################
		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			self.wndDragonSoul.SetDragonSoulRefineWindow(self.wndDragonSoulRefine)
			self.wndDragonSoulRefine.SetInventoryWindows(self.wndInventory, self.wndDragonSoul)
			self.wndInventory.SetDragonSoulRefineWindow(self.wndDragonSoulRefine)

		if app.ENABLE_TITLE_SYSTEM:
			self.wndTitle = uiTitleWindow.TitleWindow()

	def __MakeDialogs(self):
		self.dlgExchange = uiExchange.ExchangeDialog()
		self.dlgExchange.LoadDialog()

#############################

		# ACCESSORY_REFINE_ADD_METIN_STONE
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()
		# END_OF_ACCESSORY_REFINE_ADD_METIN_STONE

		if app.ENABLE_TITLE_SYSTEM:
			if self.wndTitle:
				self.wndTitle.Destroy()
				del self.wndTitle

		self.wndChatLog.Destroy()
		for btn in self.questButtonList:

#############################

	def HideAllWindows(self):
		if self.wndTaskBar:
			self.wndTaskBar.Hide()

		if self.wndEnergyBar:
			self.wndEnergyBar.Hide()

		if self.wndCharacter:
			self.wndCharacter.Hide()

		if self.wndInventory:
			self.wndInventory.Hide()

		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			self.wndDragonSoul.Hide()
			self.wndDragonSoulRefine.Hide()

		if self.wndChat:
			self.wndChat.Hide()

		if self.wndMiniMap:
			self.wndMiniMap.Hide()

		if self.wndMessenger:
			self.wndMessenger.Hide()

		if self.wndGuild:
			self.wndGuild.Hide()

		if self.wndExpandedTaskBar:
			self.wndExpandedTaskBar.Hide()

		if app.ENABLE_TITLE_SYSTEM:
			if self.wndTitle:
				self.wndTitle.Hide()

#############################
	def __HideWindows(self):
		hideWindows = self.wndTaskBar,\
						self.wndCharacter,\
						self.wndInventory,\
						self.wndMiniMap,\
						self.wndGuild,\
						self.wndMessenger,\
						self.wndChat,\
						self.wndParty,\
						self.wndGameButton,

		if self.wndEnergyBar:
			hideWindows += self.wndEnergyBar,

		if self.wndExpandedTaskBar:
			hideWindows += self.wndExpandedTaskBar,

		if app.ENABLE_DRAGON_SOUL_SYSTEM:
			hideWindows += self.wndDragonSoul,\
						self.wndDragonSoulRefine,
		if app.ENABLE_TITLE_SYSTEM:
			if self.wndTitle:
				hideWindows += self.wndTitle

#############################


	def BULID_ExitGuildArea(self, areaID):
		self.wndGameButton.HideBuildButton()

	if app.ENABLE_TITLE_SYSTEM:
		def ToggleTitleWindow(self):
			if player.IsObserverMode():
				return
			if self.wndTitle.IsShow():
				self.wndTitle.Hide()
			else:
				self.wndTitle.Show()

		def AddPlayerTitle(self, id, name, color = 0):
			if self.wndTitle:
				self.wndTitle.AddTitle(id, name, color)

#############################
