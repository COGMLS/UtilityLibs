#include "BuildMetadata.hpp"

VersionLib::BuildMetadata::BuildMetadata()
{
	this->blockMetadataMod = false;
}

VersionLib::BuildMetadata::BuildMetadata(std::string str_metadata)
{
	this->metadata.reset(new std::string);
	*this->metadata = str_metadata;
	this->blockMetadataMod = true;
}

VersionLib::BuildMetadata::BuildMetadata(const VersionLib::BuildMetadata &other)
{
	if (other.metadata)
	{
		this->metadata.reset(new std::string);
		*this->metadata = *other.metadata;
	}

	this->blockMetadataMod = other.blockMetadataMod;
}

VersionLib::BuildMetadata::BuildMetadata(VersionLib::BuildMetadata &&other) noexcept
{
	if (other.metadata)
	{
		this->metadata = std::move(other.metadata);
	}

	this->blockMetadataMod = std::move(other.blockMetadataMod);
}

VersionLib::BuildMetadata::~BuildMetadata()
{
	if (this->metadata)
	{
		this->metadata.reset(nullptr);
	}
}

VersionLib::BuildMetadata::operator bool()
{
	if (this->metadata) return true;
	return false;
}

VersionLib::BuildMetadata &VersionLib::BuildMetadata::operator=(const VersionLib::BuildMetadata &other)
{
	if (!this->blockMetadataMod)
	{
		if (other.metadata)
		{
			if (!this->metadata)
			{
				this->metadata.reset(new std::string);
			}
			*this->metadata = *other.metadata;
		}
		else
		{
			if (this->metadata)
			{
				this->metadata.reset(nullptr);
			}
		}
	
		this->blockMetadataMod = other.blockMetadataMod;
	}
	return *this;
}

VersionLib::BuildMetadata &VersionLib::BuildMetadata::operator=(VersionLib::BuildMetadata &&other) noexcept
{
	if (this->blockMetadataMod)
	{
		if (other.metadata)
		{
			if (this->metadata)
			{
				this->metadata.reset(nullptr);
			}
			this->metadata = std::move(other.metadata);
		}
		else
		{
			if (this->metadata)
			{
				this->metadata.reset(nullptr);
			}
		}
	
		this->blockMetadataMod = std::move(other.blockMetadataMod);
	}
	return *this;
}

VersionLib::BuildMetadata &VersionLib::BuildMetadata::operator=(std::string &str_metadata)
{
	if (!this->blockMetadataMod)
	{
		if (!this->metadata)
		{
			this->metadata.reset(new std::string);
		}
		*this->metadata = str_metadata;
	}
	return *this;
}

bool VersionLib::BuildMetadata::operator==(const VersionLib::BuildMetadata &other)
{
	if (this->metadata && other.metadata)
	{
		return *this->metadata.get() == *other.metadata.get();
	}
    return false;
}

bool VersionLib::BuildMetadata::operator==(std::string &other)
{
	if (this->metadata)
	{
		return *this->metadata.get() == other;
	}
    return false;
}

bool VersionLib::BuildMetadata::isEmpty()
{
	if (this->metadata)
	{
		return this->metadata.get()->empty();
	}

	return true;
}

bool VersionLib::BuildMetadata::getMetadataBlocked()
{
    return this->blockMetadataMod;
}

void VersionLib::BuildMetadata::setMetadataBlocked(bool block)
{
	this->blockMetadataMod = block;
}

std::string VersionLib::BuildMetadata::getRawMetadata()
{
	if (this->metadata)
	{
		return *this->metadata.get();
	}
    return std::string();
}
