// Inside bool CInstanceBase::Create(const SCreateData& c_rkCreateData)
// After :

 	SetAttackSpeed(c_rkCreateData.m_dwAtkSpd);

// Add :

#ifdef ENABLE_TITLE_SYSTEM
	SetTitleID(c_rkCreateData.m_dwTitleID);
#endif

// Add at the end :

#ifdef ENABLE_TITLE_SYSTEM
void CInstanceBase::SetTitleID(DWORD dwTitleID)
{
	m_dwTitleID = dwTitleID;
	// TraceError("SetTitleID %u", m_dwTitleID);
	RefreshTextTailTitle();
}

D3DXCOLOR * CInstanceBase::GetPlayerTitleColor()
{
	TTitleTable* pTable = GetTitleByID(m_dwTitleID);
	if (!pTable)
		return nullptr;
	return &pTable->color;
}

std::string CInstanceBase::GetTitleNameString()
{
	TTitleTable* pTable = GetTitleByID(m_dwTitleID);
	if (!pTable)
		return "";
	return pTable->szName;
}
#endif
