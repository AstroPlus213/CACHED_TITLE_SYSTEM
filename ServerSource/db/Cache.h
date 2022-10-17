// Add :

#ifdef ENABLE_TITLE_SYSTEM_CACHE
class CPlayerTitleCache : public cache<TPlayerTitle>
{
public:
	CPlayerTitleCache();
	~CPlayerTitleCache();
	void SetDeleted() { m_bMarkDeleted = true; }
	virtual void OnFlush();
private:
	bool m_bMarkDeleted = false;
};
#endif
