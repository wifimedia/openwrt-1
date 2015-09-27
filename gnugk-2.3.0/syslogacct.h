/*
 * syslogacct.h
 *
 * accounting module for GNU Gatekeeper that send it's output to the syslog. 
 *
 * Copyright (c) 2006, Jan Willamowius
 *
 * This work is published under the GNU Public License (GPL)
 * see file COPYING for details.
 * We also explicitly grant the right to link this code
 * with the OpenH323 library.
 *
 * $Log: syslogacct.h,v $
 * Revision 1.2  2009/02/09 13:25:59  willamowius
 * typo in comment
 *
 * Revision 1.1  2006/06/30 08:07:05  willamowius
 * new accounting module SyslogAcct
 *
 *
 */

#ifndef __SYSLOGACCT_H
#define __SYSLOGACCT_H "@(#) $Id: syslogacct.h,v 1.2 2009/02/09 13:25:59 willamowius Exp $"
#ifndef _WIN32

#include "gkacct.h"


/** Accounting module for syslog.
	It sends accounting call start/stop/update/connect events
	to syslog.
*/
class SyslogAcct : public GkAcctLogger
{
public:
	enum Constants
	{
		/// events recognized by this module
		SyslogAcctEvents = AcctStart | AcctStop | AcctUpdate | AcctConnect
	};

	SyslogAcct( 
		/// name from Gatekeeper::Acct section
		const char* moduleName,
		/// config section name to be used with an instance of this module,
		/// pass NULL to use a default section (named "moduleName")
		const char* cfgSecName = NULL
		);
		
	/// Destroy the accounting logger
	virtual ~SyslogAcct();

	/// overriden from GkAcctLogger
	virtual Status Log(
		AcctEvent evt,
		const callptr& call
		);

	/// overriden from GkAcctLogger
	virtual PString EscapeAcctParam(const PString& param) const;
		
private:
	SyslogAcct();
	/* No copy constructor allowed */
	SyslogAcct(const SyslogAcct&);
	/* No operator= allowed */
	SyslogAcct& operator=(const SyslogAcct&);

private:
	/// parametrized string for the call start event
	PString m_startEvent;
	/// parametrized string for the call stop (disconnect) event
	PString m_stopEvent;
	/// parametrized string for the call update event
	PString m_updateEvent;
	/// parametrized string for the call connect event
	PString m_connectEvent;
	/// timestamp formatting string
	PString m_timestampFormat;
};

#endif // not _WIN32
#endif /* __SYSLOGACCT_H */
