// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#include "stdafx.h"
#include "ResumeAllTrigger.h"
#include "TriggerConnection.h"
#include "DefaultTriggerUtils.h"
#include "Common/IImpl.h"

namespace CryAudio
{
//////////////////////////////////////////////////////////////////////////
CResumeAllTrigger::~CResumeAllTrigger()
{
	CRY_ASSERT_MESSAGE(m_connections.empty(), "There are still connections during %s", __FUNCTION__);
}

//////////////////////////////////////////////////////////////////////////
void CResumeAllTrigger::Execute() const
{
	if (!m_connections.empty())
	{
		ExecuteDefaultTriggerConnections(this, m_connections);
	}
	else
	{
		g_pIImpl->ResumeAll();
	}
}

//////////////////////////////////////////////////////////////////////////
void CResumeAllTrigger::AddConnections(TriggerConnections const& connections)
{
	CRY_ASSERT_MESSAGE(m_connections.empty(), "There are still connections during %s", __FUNCTION__);
	m_connections = connections;
}

//////////////////////////////////////////////////////////////////////////
void CResumeAllTrigger::Clear()
{
	for (auto const pConnection : m_connections)
	{
		delete pConnection;
	}

	m_connections.clear();
}
} // namespace CryAudio