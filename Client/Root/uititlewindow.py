## This is lenNt's dog shit script
import ui
import net
import localeInfo

class TitleWindow(ui.BoardWithTitleBar):
	def __init__(self):
		ui.BoardWithTitleBar.__init__(self)

		self.LoadWindow()

	def __del__(self):
		ui.BoardWithTitleBar.__del__(self)

	def Destroy(self):
		self.Hide()

	def LoadWindow(self):
		self.SetSize(200, 5 * 45)
		self.AddFlag("movable")
		self.AddFlag("float")
		self.SetTitleName("Title System")
		self.SetCenterPosition()
		self.SetCloseEvent(self.Close)
		
		self.TitleText = ui.TextLine()
		self.TitleText.SetParent(self)
		self.TitleText.SetPosition(0, 30)
		self.TitleText.SetText("Choose")
		self.TitleText.SetWindowHorizontalAlignCenter()
		self.TitleText.SetHorizontalAlignCenter()
		self.TitleText.Show()
		
		self.TitleListBase = ui.SlotBar()
		self.TitleListBase.SetParent(self)
		self.TitleListBase.SetSize(200 - 40, 140)
		self.TitleListBase.SetPosition(19, 44)
		self.TitleListBase.Show()
		
		self.TitleList = ui.ListBox()
		self.TitleList.SetParent(self.TitleListBase)
		self.TitleList.SetSize(200 - 40, 136)
		self.TitleList.SetPosition(0, 0)
		self.TitleList.Show()
		
		self.TitleListScrollBar = ui.ScrollBar()
		self.TitleListScrollBar.SetParent(self.TitleListBase)
		self.TitleListScrollBar.SetPosition(19, 7)
		self.TitleListScrollBar.SetScrollBarSize(130)
		self.TitleListScrollBar.SetWindowHorizontalAlignRight()
		self.TitleListScrollBar.SetScrollEvent(ui.__mem_func__(self.OnScrollList))
		self.TitleListScrollBar.Show()
		
		self.TitleList.ClearItem()

		self.ChooseButton = ui.Button()
		self.ChooseButton.SetParent(self)
		self.ChooseButton.SetPosition(60, 192)
		self.ChooseButton.SetUpVisual("d:/ymir work/ui/public/Large_button_01.sub")
		self.ChooseButton.SetOverVisual("d:/ymir work/ui/public/Large_button_02.sub")
		self.ChooseButton.SetDownVisual("d:/ymir work/ui/public/Large_button_03.sub")
		self.ChooseButton.SetEvent(ui.__mem_func__(self.__ClickTitleButton))
		self.ChooseButton.SetText("Choose")
		self.ChooseButton.ButtonText.SetFontColor(1, 1, 1)
		self.ChooseButton.Show()

	def OnScrollList(self):
		viewItemCount = self.TitleList.GetViewItemCount()
		itemCount = self.TitleList.GetItemCount()
		pos = self.TitleListScrollBar.GetPos() * (itemCount - viewItemCount)
		self.TitleList.SetBasePos(int(pos))

	def Open(self):
		self.Show()

	def AddTitle(self, id, name, color = 0):
		self.TitleList.InsertItem(id, name)

	def __ClickTitleButton(self):
		if self.TitleList.GetSelectedItem():
			net.SendPlayerSetTitlePacket(self.TitleList.GetSelectedItem())

	def Close(self):
		self.Hide()

	def OnPressEscapeKey(self):
		self.Close()
		return True
