/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libodfgen
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002-2003 William Lachance (wrlach@gmail.com)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef _DOCUMENTELEMENT_HXX_
#define _DOCUMENTELEMENT_HXX_

#include <vector>
#include <librevenge/librevenge.h>
#include <libodfgen/libodfgen.hxx>

class DocumentElement
{
public:
	virtual ~DocumentElement() {}
	virtual void write(OdfDocumentHandler *pHandler) const = 0;
	virtual void print() const {}
};

class TagElement : public DocumentElement
{
public:
	~TagElement() override {}
	TagElement(const librevenge::RVNGString &szTagName) : msTagName(szTagName) {}
	const librevenge::RVNGString &getTagName() const
	{
		return msTagName;
	}
	void print() const override;
private:
	librevenge::RVNGString msTagName;
};

class TagOpenElement : public TagElement
{
public:
	TagOpenElement(const librevenge::RVNGString &szTagName) : TagElement(szTagName), maAttrList() {}
	~TagOpenElement() override {}
	void addAttribute(const librevenge::RVNGString &szAttributeName,
	                  const librevenge::RVNGString &sAttributeValue, bool forceString=true);
	void write(OdfDocumentHandler *pHandler) const override;
	void print() const override;
private:
	librevenge::RVNGPropertyList maAttrList;
};

class TagCloseElement : public TagElement
{
public:
	TagCloseElement(const librevenge::RVNGString &szTagName) : TagElement(szTagName) {}
	~TagCloseElement() override {}
	void write(OdfDocumentHandler *pHandler) const override;
};

class CharDataElement : public DocumentElement
{
public:
	CharDataElement(const librevenge::RVNGString &sData) : DocumentElement(), msData(sData) {}
	~CharDataElement() override {}
	void write(OdfDocumentHandler *pHandler) const override;
private:
	librevenge::RVNGString msData;
};

class TextElement : public DocumentElement
{
public:
	TextElement(const librevenge::RVNGString &sTextBuf) : DocumentElement(), msTextBuf(sTextBuf) {}
	~TextElement() override {}
	void write(OdfDocumentHandler *pHandler) const override;

private:
	librevenge::RVNGString msTextBuf;
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
