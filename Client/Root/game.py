	if app.ENABLE_TITLE_SYSTEM:
		def BINARY_SetPlayerTitle(self, title_id, name):
			# if title_id:
				# import chat
				# chat.AppendChat(chat.CHAT_TYPE_INFO, "title %d added".format(title_id))
			if self.interface:
				self.interface.AddPlayerTitle(title_id, name)

		def ToggleTitleWindow(self):
			if self.interface:
				self.interface.ToggleTitleWindow()

