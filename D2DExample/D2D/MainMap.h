#pragma once
#include "NNRect.h"

class CMainMap : public NNObject
{
public:
	CMainMap(void);
	virtual ~CMainMap(void);

	void Render();
	void Update( float dTime );

	NNRect * GetMainFrame() {return m_MainFrame;}


	NNCREATE_FUNC(CMainMap);

private:
	NNRect * m_MainFrame;
};
