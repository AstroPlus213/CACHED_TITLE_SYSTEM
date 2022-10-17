// Replace :

const float c_fyGuildNamePosition = 15.0f;
const float c_fyMarkPosition = 15.0f + 11.0f;

// With :

#ifdef ENABLE_TITLE_SYSTEM
const float c_fyPlayerTitlePosition = 15.0f;
const float c_fyGuildNamePosition = 15.0f + 15.0f;
const float c_fyMarkPosition = 15.0f + 11.0f + 15.0f;
#else
const float c_fyGuildNamePosition = 15.0f;
const float c_fyMarkPosition = 15.0f + 11.0f;
#endif

// Inside void CPythonTextTail::ArrangeTextTail()
// After :

 			pGuildNameInstance->SetPosition(pTextTail->x + iImageHalfSize, pTextTail->y - c_fyGuildNamePosition, pTextTail->z);
 			pGuildNameInstance->Update();
 		}

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		auto pPlayerTitleInstance = pTextTail->pPlayerTitleTextInstance;
		if (pPlayerTitleInstance)
		{
			pPlayerTitleInstance->SetPosition(pTextTail->x, pTextTail->y - c_fyPlayerTitlePosition, pTextTail->z);
			pPlayerTitleInstance->Update();
			
		}
#endif

// Inside void CPythonTextTail::Render()
// After :

 		{
 			pTextTail->pLevelTextInstance->Render();
 		}

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		if (pTextTail->pPlayerTitleTextInstance)
		{
			pTextTail->pPlayerTitleTextInstance->Render();
		}
#endif

// Inside void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtual
// After :

 	pTextTail->pLevelTextInstance=NULL;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	pTextTail->pPlayerTitleTextInstance=NULL;
#endif

// Inside void CPythonTextTail::RegisterCharacterTextTail(DWORD dwGuildID, DWORD dwVirtual
// After :

 		prGuildNameInstance->SetValue(strGuildName.c_str());
 		prGuildNameInstance->SetColor(c_TextTail_Guild_Name_Color.r, c_TextTail_Guild_Name_Color.g, c_TextTail_Guild_Name_Color.b);
 		prGuildNameInstance->Update();

// Add :

#ifdef ENABLE_TITLE_SYSTEM
		CGraphicTextInstance*& pPlayerTitleInstance = pTextTail->pPlayerTitleTextInstance;
		if (pPlayerTitleInstance)
		{
			pPlayerTitleInstance = CGraphicTextInstance::New();
			pPlayerTitleInstance->SetTextPointer(ms_pFont);
			pPlayerTitleInstance->SetOutline(true);
			pPlayerTitleInstance->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
			pPlayerTitleInstance->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
			std::string stTitle = /*"[" + */pCharacterInstance->GetTitleNameString()/* + "]"*/;
			pPlayerTitleInstance->SetValue(stTitle.c_str());
			D3DXCOLOR* pPlayerTitleColor = pCharacterInstance->GetPlayerTitleColor();
			pPlayerTitleInstance->SetColor(pPlayerTitleColor->r, pPlayerTitleColor->g, pPlayerTitleColor->b);
			pPlayerTitleInstance->Update();
		}
#endif

// Inside CPythonTextTail::TTextTail * CPythonTextTail::RegisterTextTail(DWORD dwVirtualID
// After :

 	pTextTail->pLevelTextInstance = NULL;

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	pTextTail->pPlayerTitleTextInstance = NULL;
#endif

// Inside void CPythonTextTail::DeleteTextTail
// After :

 		CGraphicTextInstance::Delete(pTextTail->pGuildNameTextInstance);
 		pTextTail->pGuildNameTextInstance = NULL;
 	}

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	if (pTextTail->pPlayerTitleTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pPlayerTitleTextInstance);
		pTextTail->pPlayerTitleTextInstance = nullptr;
	}
#endif

// Before void CPythonTextTail::DetachTitle(DWORD dwVID)
// Add :

#ifdef ENABLE_TITLE_SYSTEM
void CPythonTextTail::AttachPlayerTitle(DWORD dwVID, const char* c_szName, const D3DXCOLOR& c_rColor)
{
	CInstanceBase * pInstance = CPythonCharacterManager::Instance().GetInstancePtr(dwVID);
	if (!pInstance)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail* pTextTail = itor->second;
	CGraphicTextInstance*& prTitle = pTextTail->pPlayerTitleTextInstance;
	if (!prTitle)
	{
		prTitle = CGraphicTextInstance::New();
		prTitle->SetTextPointer(ms_pFont);
		prTitle->SetOutline(true);
		if (LocaleService_IsEUROPE())
			prTitle->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_RIGHT);
		else
			prTitle->SetHorizonalAlign(CGraphicTextInstance::HORIZONTAL_ALIGN_CENTER);
		prTitle->SetVerticalAlign(CGraphicTextInstance::VERTICAL_ALIGN_BOTTOM);
	}

	prTitle->SetValue(c_szName);
	// TODO: Change it when done
	// TraceError("color: %.1f, %.1f, %.1f", c_rColor.r, c_rColor.g, c_rColor.b);
	prTitle->SetColor(c_rColor.r, c_rColor.g, c_rColor.b);
	prTitle->Update();
}

void CPythonTextTail::DetachPlayerTitle(DWORD dwVID)
{
	if (!bPKTitleEnable)
		return;

	TTextTailMap::iterator itor = m_CharacterTextTailMap.find(dwVID);
	if (m_CharacterTextTailMap.end() == itor)
		return;

	TTextTail* pTextTail = itor->second;
	if (pTextTail->pPlayerTitleTextInstance)
	{
		CGraphicTextInstance::Delete(pTextTail->pPlayerTitleTextInstance);
		pTextTail->pPlayerTitleTextInstance = NULL;
	}
}
#endif

// ! In case you have Ikarus's offline shop implented
// Inside 
// After :

// Add :

