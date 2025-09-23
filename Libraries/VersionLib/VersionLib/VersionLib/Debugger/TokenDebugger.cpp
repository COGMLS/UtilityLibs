#include "TokenDebugger.hpp"

VersionLib::Debugger::DbgToken::DbgToken(unsigned int dbgMaxEntries, bool overwrite)
{
	this->pDbgEntries.reset(new std::vector<std::string>());
	this->dbg_max_entries = dbg_max_entries;
	this->dbg_entries = 0;
	this->overwrite = overwrite;
}

VersionLib::Debugger::DbgToken::~DbgToken()
{
	this->dbg_entries = 0;
	this->dbg_max_entries = 0;
	this->pDbgEntries.reset(nullptr);
}

VersionLib::Debugger::DbgToken &VersionLib::Debugger::DbgToken::operator=(const VersionLib::Debugger::DbgToken &other)
{
	if (this == &other)
	{
		return *this;
	}

	this->dbg_entries = other.dbg_entries;
	this->dbg_max_entries = other.dbg_max_entries;
	this->overwrite = other.overwrite;
	*this->pDbgEntries = *other.pDbgEntries;

	return *this;
}

VersionLib::Debugger::DbgToken &VersionLib::Debugger::DbgToken::operator=(VersionLib::Debugger::DbgToken &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->dbg_entries = std::move(other.dbg_entries);
	this->dbg_max_entries = std::move(other.dbg_max_entries);
	this->overwrite = std::move(other.overwrite);
	this->pDbgEntries = std::move(other.pDbgEntries);

	return *this;
}

void VersionLib::Debugger::DbgToken::push_log(std::string entry)
{
	// If the vector is full and the policy of new entries is remove the older values,
	// remove the first component.
	if (this->dbg_entries + 1 == this->dbg_max_entries && this->overwrite)
	{
		this->pDbgEntries->erase(this->pDbgEntries->begin());
		this->dbg_entries--;
	}

	if (this->dbg_entries + 1 < this->dbg_max_entries)
	{
		this->pDbgEntries->push_back(entry);
		this->dbg_entries++;
	}
}

std::unique_ptr<std::vector<std::string>> VersionLib::Debugger::DbgToken::export_log()
{
	std::unique_ptr<std::vector<std::string>> pLog;

	pLog.swap(this->pDbgEntries);
	pDbgEntries.reset(new std::vector<std::string>);
	this->dbg_entries = 0;

	return pLog;
}
