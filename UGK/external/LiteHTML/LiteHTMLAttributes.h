/**
 *	PROJECT - HTML Reader Class Library
 *
 *	LiteHTMLAttributes.h - Defines CLiteHTMLAttributes and 
 *	                       CLiteHTMLElemAttr
 *	
 *	Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
 *	Copyright (c) 2004. All rights reserved.
 *
 *	This code may be used in compiled form in any way you desire 
 *	(including commercial use). The code may be redistributed 
 *	unmodified by any means PROVIDING it is not sold for profit 
 *	without the authors written consent, and providing that this 
 *	notice and the authors name and all copyright notices remains 
 *	intact. However, this file and the accompanying source code may 
 *	not be hosted on a website or bulletin board without the authors 
 *	written permission.
 *	
 *	This file is provided "AS IS" with no expressed or implied warranty.
 *	The author accepts no liability for any damage/loss of business that
 *	this product may cause.
 *
 *	Although it is not necessary, but if you use this code in any of 
 *	your application (commercial or non-commercial), please INFORM me 
 *	so that I may know how useful this library is. This will encourage 
 *	me to keep updating it.
 *
 *	HISTORY:
 *
 *	Version 1.0				Gurmeet S. Kochar (GSK)
 *	Mar 18, 2004			First release version.
 */
#ifndef __LITEHTMLATTRIBUTES_H__ //Se borra la macro LITEHTMLATTRIBUTES
#define __LITEHTMLATTRIBUTES_H__ //Se define la macro LITEHTMLATTRIBUTES

#include <LiteHTMLEntityResolver.h>

#pragma warning(push, 4)
#pragma warning (disable : 4290)	// C++ Exception Specification ignored

class CLiteHTMLAttributes;	// forward declaration

/**   
   @class  CLiteHTMLElemAttr
   Class is defined LiteHTMLElemAttr    
   Where is the builder, assistant attributes, operators   
   Here defined colors, labels and color operations for characters
*/
class CLiteHTMLElemAttr
{
	// Friends
	friend class CLiteHTMLAttributes;

// Constructors
public:
	CLiteHTMLElemAttr(LPCTSTR lpszAttribName = NULL, 
					  LPCTSTR lpszAttribValue = NULL)
	{
		Init();
		m_strAttrName = lpszAttribName;
		m_strAttrValue = lpszAttribValue;
	}

	CLiteHTMLElemAttr(const CLiteHTMLElemAttr &rSource)
	{
		Init();
		m_strAttrName = rSource.m_strAttrName;
		m_strAttrValue = rSource.m_strAttrValue;
	}

// Initialization Helpers
private:
	static void Init(void)
	{
		if (_namedColors.GetCount())
			return;

		/** 28 system colors */
		_namedColors[LPCWSTR("activeborder")] = (COLORREF)0x8000000A;
		_namedColors[LPCWSTR("activecaption")] = (COLORREF)0x80000002;
		_namedColors[LPCWSTR("appworkspace")]		= (COLORREF)0x8000000C;
		_namedColors[LPCWSTR("background")]			= (COLORREF)0x80000001;
		_namedColors[LPCWSTR("buttonface")]			= (COLORREF)0x8000000F;
		_namedColors[LPCWSTR("buttonhighlight")]		= (COLORREF)0x80000014;
		_namedColors[LPCWSTR("buttonshadow")]		= (COLORREF)0x80000010;
		_namedColors[LPCWSTR("buttontext")]			= (COLORREF)0x80000012;
		_namedColors[LPCWSTR("captiontext")]			= (COLORREF)0x80000009;
		_namedColors[LPCWSTR("graytext")]			= (COLORREF)0x80000011;
		_namedColors[LPCWSTR("highlight")]			= (COLORREF)0x8000000D;
		_namedColors[LPCWSTR("highlighttext")]		= (COLORREF)0x8000000E;
		_namedColors[LPCWSTR("inactiveborder")]		= (COLORREF)0x8000000B;
		_namedColors[LPCWSTR("inactivecaption")]		= (COLORREF)0x80000003;
		_namedColors[LPCWSTR("inactivecaptiontext")]	= (COLORREF)0x80000013;
		_namedColors[LPCWSTR("infobackground")]		= (COLORREF)0x80000018;
		_namedColors[LPCWSTR("infotext")]			= (COLORREF)0x80000017;
		_namedColors[LPCWSTR("menu")]				= (COLORREF)0x80000004;
		_namedColors[LPCWSTR("menutext")]			= (COLORREF)0x80000007;
		_namedColors[LPCWSTR("scrollbar")]			= (COLORREF)0x80000000;
		_namedColors[LPCWSTR("threeddarkshadow")]	= (COLORREF)0x80000015;
		_namedColors[LPCWSTR("threedface")]			= (COLORREF)0x8000000F;
		_namedColors[LPCWSTR("threedhighlight")]		= (COLORREF)0x80000014;
		_namedColors[LPCWSTR("threedlightshadow")]	= (COLORREF)0x80000016;
		_namedColors[LPCWSTR("threedshadow")]		= (COLORREF)0x80000010;
		_namedColors[LPCWSTR("Window")]				= (COLORREF)0x80000005;
		_namedColors[LPCWSTR("windowframe")]			= (COLORREF)0x80000006;
		_namedColors[LPCWSTR("windowtext")]			= (COLORREF)0x80000008;

		/** 16 basic colors */
		_namedColors[LPCWSTR("black")]				= RGB(0x00, 0x00, 0x00);
		_namedColors[LPCWSTR("gray")]				= RGB(0x80, 0x80, 0x80);
		_namedColors[LPCWSTR("silver")]				= RGB(0xC0, 0xC0, 0xC0);
		_namedColors[LPCWSTR("white")]				= RGB(0xFF, 0xFF, 0xFF);
		_namedColors[LPCWSTR("yellow")]				= RGB(0xFF, 0xFF, 0x00);
		_namedColors[LPCWSTR("olive")]				= RGB(0x80, 0x80, 0x00);
		_namedColors[LPCWSTR("red")]					= RGB(0xFF, 0x00, 0x00);
		_namedColors[LPCWSTR("maroon")]				= RGB(0x80, 0x00, 0x00);
		_namedColors[LPCWSTR("fuchsia")]				= RGB(0xFF, 0x00, 0xFF);
		_namedColors[LPCWSTR("purple")]				= RGB(0x80, 0x00, 0x80);
		_namedColors[LPCWSTR("blue")]				= RGB(0x00, 0x00, 0xFF);
		_namedColors[LPCWSTR("navy")]				= RGB(0x00, 0x00, 0x80);
		_namedColors[LPCWSTR("aqua")]				= RGB(0x00, 0xFF, 0xFF);
		_namedColors[LPCWSTR("teal")]				= RGB(0x00, 0x80, 0x80);
		_namedColors[LPCWSTR("lime")]				= RGB(0x00, 0xFF, 0x00);
		_namedColors[LPCWSTR("green")]				= RGB(0x00, 0x80, 0xFF);

		/** additional named colors */
		_namedColors[LPCWSTR("darkolivegreen")]		= RGB(0x55, 0x6B, 0x2F);
		_namedColors[LPCWSTR("olivedrab")]			= RGB(0x6B, 0x8E, 0x23);
		_namedColors[LPCWSTR("yellowgreen")]			= RGB(0x9A, 0xCD, 0x32);
		_namedColors[LPCWSTR("lawngreen")]			= RGB(0x7C, 0xFC, 0x00);
		_namedColors[LPCWSTR("chartreuse")]			= RGB(0x7F, 0xFF, 0x00);
		_namedColors[LPCWSTR("greenyellow")]			= RGB(0xAD, 0xFF, 0x2F);
		_namedColors[LPCWSTR("palegreen")]			= RGB(0x98, 0xFB, 0x98);
		_namedColors[LPCWSTR("lightgreen")]			= RGB(0x90, 0xEE, 0x90);
		_namedColors[LPCWSTR("darkgreen")]			= RGB(0x00, 0x64, 0x00);
		_namedColors[LPCWSTR("forestgreen")]			= RGB(0x22, 0x8B, 0x22);
		_namedColors[LPCWSTR("seagreen")]			= RGB(0x2E, 0x8B, 0x57);
		_namedColors[LPCWSTR("mediumseagreen")]		= RGB(0x3C, 0xB3, 0x71);
		_namedColors[LPCWSTR("limegreen")]			= RGB(0x32, 0xCD, 0x32);
		_namedColors[LPCWSTR("darkseagreen")]		= RGB(0x8F, 0xBC, 0x8B);
		_namedColors[LPCWSTR("springgreen")]			= RGB(0x00, 0xFF, 0x7F);
		_namedColors[LPCWSTR("mediumspringgreen")]	= RGB(0x00, 0xFA, 0x99);
		_namedColors[LPCWSTR("darkslategray")]		= RGB(0x2F, 0x4F, 0x4F);
		_namedColors[LPCWSTR("darkcyan")]			= RGB(0x00, 0x8B, 0x8B);
		_namedColors[LPCWSTR("cadetblue")]			= RGB(0x5F, 0x9E, 0xA0);
		_namedColors[LPCWSTR("lightseagreen")]		= RGB(0x20, 0xB2, 0xAA);
		_namedColors[LPCWSTR("mediumaquamarine")]	= RGB(0x66, 0xCD, 0xAA);
		_namedColors[LPCWSTR("turquoise")]			= RGB(0x40, 0xE0, 0xD0);
		_namedColors[LPCWSTR("aquamarine")]			= RGB(0x7F, 0xFF, 0xD4);
		_namedColors[LPCWSTR("paleturquoise")]		= RGB(0xAF, 0xEE, 0xEE);
		_namedColors[LPCWSTR("slategray")]			= RGB(0x70, 0x80, 0x90);
		_namedColors[LPCWSTR("lightslategray")]		= RGB(0x77, 0x88, 0x99);
		_namedColors[LPCWSTR("steelblue")]			= RGB(0x46, 0x82, 0xB4);
		_namedColors[LPCWSTR("deepskyblue")]			= RGB(0x00, 0xBF, 0xFF);
		_namedColors[LPCWSTR("darkturquoise")]		= RGB(0x00, 0xCE, 0xD1);
		_namedColors[LPCWSTR("mediumturquoise")]		= RGB(0x48, 0xD1, 0xCC);
		_namedColors[LPCWSTR("powderblue")]			= RGB(0xB0, 0xE0, 0xE6);
		_namedColors[LPCWSTR("lightcyan")]			= RGB(0xE0, 0xFF, 0xFF);
		_namedColors[LPCWSTR("darkblue")]			= RGB(0x00, 0x00, 0x8B);
		_namedColors[LPCWSTR("mediumblue")]			= RGB(0x00, 0x00, 0xCD);
		_namedColors[LPCWSTR("royalblue")]			= RGB(0x41, 0x69, 0xe1);
		_namedColors[LPCWSTR("dodgerblue")]			= RGB(0x1E, 0x90, 0xFF);
		_namedColors[LPCWSTR("cornflowerblue")]		= RGB(0x64, 0x95, 0xED);
		_namedColors[LPCWSTR("skyblue")]				= RGB(0x87, 0xCE, 0xEB);
		_namedColors[LPCWSTR("lightskyblue")]		= RGB(0x87, 0xCE, 0xFA);
		_namedColors[LPCWSTR("lightblue")]			= RGB(0xAD, 0xD8, 0xE6);
		_namedColors[LPCWSTR("midnightblue")]		= RGB(0x19, 0x19, 0x70);
		_namedColors[LPCWSTR("darkslateblue")]		= RGB(0x48, 0x3D, 0x8B);
		_namedColors[LPCWSTR("blueviolet")]			= RGB(0x8A, 0x2B, 0xE2);
		_namedColors[LPCWSTR("slateblue")]			= RGB(0x6A, 0x5A, 0xCD);
		_namedColors[LPCWSTR("mediumslateblue")]		= RGB(0x7B, 0x68, 0xEE);
		_namedColors[LPCWSTR("mediumpurple")]		= RGB(0x93, 0x70, 0xDB);
		_namedColors[LPCWSTR("lightsteelblue")]		= RGB(0xB0, 0xC4, 0xDE);
		_namedColors[LPCWSTR("lavender")]			= RGB(0xE6, 0xE6, 0xFA);
		_namedColors[LPCWSTR("indigo")]				= RGB(0x4B, 0x00, 0x82);
		_namedColors[LPCWSTR("darkviolet")]			= RGB(0x94, 0x00, 0xD3);
		_namedColors[LPCWSTR("darkorchid")]			= RGB(0x99, 0x32, 0xCC);
		_namedColors[LPCWSTR("mediumorchid")]		= RGB(0xBA, 0x55, 0xD3);
		_namedColors[LPCWSTR("orchid")]				= RGB(0xDA, 0x70, 0xD6);
		_namedColors[LPCWSTR("violet")]				= RGB(0xEE, 0x82, 0xEE);
		_namedColors[LPCWSTR("plum")]				= RGB(0xDD, 0xA0, 0xDD);
		_namedColors[LPCWSTR("thistle")]				= RGB(0xD8, 0xDF, 0xD8);
		_namedColors[LPCWSTR("darkmagenta")]			= RGB(0x8B, 0x00, 0x8B);
		_namedColors[LPCWSTR("mediumvioletred")]		= RGB(0xC7, 0x15, 0x85);
		_namedColors[LPCWSTR("deeppink")]			= RGB(0xFF, 0x14, 0x93);
		_namedColors[LPCWSTR("palmvioletred")]		= RGB(0xDB, 0x70, 0x93);
		_namedColors[LPCWSTR("hotpink")]				= RGB(0xFF, 0x69, 0xB4);
		_namedColors[LPCWSTR("lightpink")]			= RGB(0xFF, 0xB6, 0xC1);
		_namedColors[LPCWSTR("pink")]				= RGB(0xFF, 0xC0, 0xCB);
		_namedColors[LPCWSTR("mistyrose")]			= RGB(0xFF, 0xE4, 0xE1);
		_namedColors[LPCWSTR("brown")]				= RGB(0xA5, 0x2A, 0x2A);
		_namedColors[LPCWSTR("indianred")]			= RGB(0xCD, 0x5C, 0x5C);
		_namedColors[LPCWSTR("rosybrown")]			= RGB(0xBC, 0x8F, 0x8F);
		_namedColors[LPCWSTR("salmon")]				= RGB(0xFA, 0x80, 0x72);
		_namedColors[LPCWSTR("lightcoral")]			= RGB(0xF0, 0x80, 0x80);
		_namedColors[LPCWSTR("darksalmon")]			= RGB(0xE9, 0x96, 0x7A);
		_namedColors[LPCWSTR("lightsalmon")]			= RGB(0xFF, 0xA0, 0x7A);
		_namedColors[LPCWSTR("peachpuff")]			= RGB(0xFF, 0xDA, 0xB9);
		_namedColors[LPCWSTR("darkred")]				= RGB(0x8B, 0x00, 0x00);
		_namedColors[LPCWSTR("firebrick")]			= RGB(0xB2, 0x22, 0x22);
		_namedColors[LPCWSTR("crimson")]				= RGB(0xDC, 0x14, 0x3C);
		_namedColors[LPCWSTR("orangered")]			= RGB(0xFF, 0x45, 0x00);
		_namedColors[LPCWSTR("tomato")]				= RGB(0xFF, 0x63, 0x47);
		_namedColors[LPCWSTR("coral")]				= RGB(0xFF, 0x7F, 0x50);
		_namedColors[LPCWSTR("wheat")]				= RGB(0xF5, 0xDE, 0xB3);
		_namedColors[LPCWSTR("papayawhip")]			= RGB(0xFF, 0xEF, 0xD5);
		_namedColors[LPCWSTR("sienna")]				= RGB(0xA0, 0x52, 0x2D);
		_namedColors[LPCWSTR("chocolate")]			= RGB(0xD2, 0x69, 0x1E);
		_namedColors[LPCWSTR("darkorange")]			= RGB(0xFF, 0x8C, 0x00);
		_namedColors[LPCWSTR("sandybrown")]			= RGB(0xF4, 0xA4, 0x60);
		_namedColors[LPCWSTR("orange")]				= RGB(0xFF, 0xA5, 0x00);
		_namedColors[LPCWSTR("navajowhite")]			= RGB(0xFF, 0xDE, 0xAD);
		_namedColors[LPCWSTR("moccasin")]			= RGB(0xFF, 0xE4, 0xB5);
		_namedColors[LPCWSTR("saddlebrown")]			= RGB(0x8B, 0x45, 0x13);
		_namedColors[LPCWSTR("peru")]				= RGB(0xCD, 0x85, 0x3F);
		_namedColors[LPCWSTR("burlywood")]			= RGB(0xDE, 0xB8, 0x87);
		_namedColors[LPCWSTR("tan")]					= RGB(0xD2, 0xB4, 0x8C);
		_namedColors[LPCWSTR("bisque")]				= RGB(0xFF, 0xE4, 0xC4);
		_namedColors[LPCWSTR("blanchedalmond")]		= RGB(0xFF, 0xEB, 0xCD);
		_namedColors[LPCWSTR("antiquewhite")]		= RGB(0xFA, 0xEB, 0xD7);
		_namedColors[LPCWSTR("darkgoldenrod")]		= RGB(0xB8, 0x86, 0x0B);
		_namedColors[LPCWSTR("goldenrod")]			= RGB(0xDA, 0xA5, 0x20);
		_namedColors[LPCWSTR("darkkhaki")]			= RGB(0xBD, 0xB7, 0x6B);
		_namedColors[LPCWSTR("gold")]				= RGB(0xFF, 0xD7, 0x00);
		_namedColors[LPCWSTR("khaki")]				= RGB(0xF0, 0xE6, 0x8C);
		_namedColors[LPCWSTR("palegoldenrod")]		= RGB(0xEE, 0xE8, 0xAA);
		_namedColors[LPCWSTR("lemonchiffon")]		= RGB(0xFF, 0xFA, 0xCD);
		_namedColors[LPCWSTR("beige")]				= RGB(0xF5, 0xF5, 0xDC);
		_namedColors[LPCWSTR("lightgoldenrodyellow")]= RGB(0xFA, 0xFA, 0xD2);
		_namedColors[LPCWSTR("lightyellow")]			= RGB(0xFF, 0xFF, 0xE0);
		_namedColors[LPCWSTR("ivory")]				= RGB(0xFF, 0xFF, 0x00);
		_namedColors[LPCWSTR("cornsilk")]			= RGB(0xFF, 0xF8, 0xDC);
		_namedColors[LPCWSTR("oldlace")]				= RGB(0xFD, 0xF5, 0xE6);
		_namedColors[LPCWSTR("florawhite")]			= RGB(0xFF, 0xFA, 0xF0);
		_namedColors[LPCWSTR("honeydew")]			= RGB(0xF0, 0xFF, 0xF0);
		_namedColors[LPCWSTR("mintcream")]			= RGB(0xF5, 0xFF, 0xFA);
		_namedColors[LPCWSTR("azure")]				= RGB(0xF0, 0xFF, 0xFF);
		_namedColors[LPCWSTR("ghostwhite")]			= RGB(0xF8, 0xF8, 0xFF);
		_namedColors[LPCWSTR("linen")]				= RGB(0xFA, 0xF0, 0xE6);
		_namedColors[LPCWSTR("seashell")]			= RGB(0xFF, 0xF5, 0xEE);
		_namedColors[LPCWSTR("snow")]				= RGB(0xFF, 0xFA, 0xFA);
		_namedColors[LPCWSTR("dimgray")]				= RGB(0x69, 0x69, 0x69);
		_namedColors[LPCWSTR("darkgray")]			= RGB(0xA9, 0xA9, 0xA9);
		_namedColors[LPCWSTR("lightgray")]			= RGB(0xD3, 0xD3, 0xD3);
		_namedColors[LPCWSTR("gainsboro")]			= RGB(0xDC, 0xDC, 0xDC);
		_namedColors[LPCWSTR("whitesmoke")]			= RGB(0xF5, 0xF5, 0xF5);
		_namedColors[LPCWSTR("ghostwhite")]			= RGB(0xF8, 0xF8, 0xFF);
		_namedColors[LPCWSTR("aliceblue")]			= RGB(0xF0, 0xF8, 0xFF);
	}

// Attributes
public:
	/**
	 * @return name of this CLiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getName(void) const
		{ return (m_strAttrName); }

	/**
	 * @return value of this CLiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getValue(void) const
		{ return (m_strAttrValue); }

	/**
	 * Determines if the attribute value is a named color value
	 * @return true if attribute value is a named color, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isNamedColorValue(void) const
	{
		if ( (m_strAttrValue.GetLength()) && (::_istalpha(m_strAttrValue[0])) )
		{
			COLORREF crTemp = _clrInvalid;
			CString	strKey(m_strAttrValue);

			strKey.MakeLower();
			if (_namedColors.Lookup(m_strAttrValue, crTemp))
				return (true);
		}
		return (false);
	}

	/**
	 * Determines if the attribute value is a named system color value
	 * @return true if value is a named system color, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isSysColorValue(void) const
	{
		if ( (m_strAttrValue.GetLength()) && (::_istalpha(m_strAttrValue[0])) )
		{
			COLORREF	crTemp = _clrInvalid;
			CString		strKey(m_strAttrValue);

			strKey.MakeLower();
			if (_namedColors.Lookup(strKey, crTemp))
				return (crTemp >= 0x80000000 && crTemp <= 0x80000018);
		}
		return (false);
	}

	/**
	 * Determines if the attribute value is a color value in 
	 * hexadecimal format
	 * @return true if attribute value is a color value, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isHexColorValue(void) const
	{
		// zero-length attribute value?
		if (m_strAttrValue.IsEmpty())
			return (false);

		if (m_strAttrValue[0] == _T('#'))
		{
			if (m_strAttrValue.GetLength() > 1)
			{
				for (int i = 1; i < m_strAttrValue.GetLength(); i++)
				{
					if (!::_istxdigit(m_strAttrValue[i]))
						return (false);
				}
				return (true);
			}
		}

		return (false);
	}

	/**
	 * Determines if the attribute value contains a color reference
	 * @return true, if attribute value is color value, false otherwise.
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isColorValue(void) const
		{ return (isNamedColorValue() || isHexColorValue()); }

	/**
	 * Returns the color value of the attribute
	 * @return a COLORREF representing the color
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	COLORREF getColorValue(void) const
	{
		COLORREF crTemp = _clrInvalid;
		if (isNamedColorValue())
		{
			CString	strKey(m_strAttrValue);
			strKey.MakeLower();
			if (_namedColors.Lookup(strKey, crTemp))
			{
				// is this a system named color value?
				if (crTemp >= 0x80000000 && crTemp <= 0x80000018)
					crTemp = ::GetSysColor(crTemp & 0x7FFFFFFF);
			}
		}
		else if (isHexColorValue())
			crTemp = ::_tcstoul(m_strAttrValue.Mid(1), NULL, 16);
		return (crTemp);
	}
	
	/**
	 * Returns the RGB value of the attribute in hexadecimal format
	 * @return hexadecimal string representing the color value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getColorHexValue(void) const
	{
		CString	strColorHex;
		if (isHexColorValue())
			strColorHex = m_strAttrValue.Mid(1);
		else
		{
			COLORREF crTemp = getColorValue();
			if (crTemp != _clrInvalid)
				strColorHex.Format(_T("#%06x"), crTemp);
		}
		return (strColorHex);
	}

	/**
	 * Checks to see if the attribute contains a percent value
	 * @return true if value is a percent value, otherwise, false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool isPercentValue(void) const
		{ return (m_strAttrValue.Right(1) == _T("%") ? true : false); }

	/**
	 * Returns a percent value of the attribute
	 * @return percentage value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	unsigned short getPercentValue(unsigned short max = _percentMax) const
	{
		ASSERT(max > 0);
		if (!isPercentValue())	return (0);
		unsigned short	percentVal = (unsigned short)((short)*this);
		return ((percentVal > max ? max : percentVal));
	}
	
	/**
	 * Parses a length value from the attribute/value 
	 * and identifies its length unit also
	 *
	 * @param rUnit - this will receive the type of the length unit
	 *
	 * @return an integer value of the attribute 
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	enum LengthUnitsEnum { em, ex, px, per, in, cm, mm, pt, pc };
	short getLengthValue(LengthUnitsEnum &rUnit) const
	{
		static const TCHAR	_szUnits[][4] = 
		{
			/** relative length units */
			_T("em"), _T("ex"), _T("px"), _T("%"), 
			/** absolute length units */
			_T("in"), _T("cm"), _T("mm"), _T("pt"), _T("pc") 
		};

		int i;
		if (m_strAttrValue.IsEmpty())
			return (0);

		for (i = 0; i < sizeof(_szUnits)/sizeof(_szUnits[0]); i++)
		{
			if (m_strAttrValue.Right(::lstrlen(_szUnits[i])). \
				CompareNoCase(_szUnits[i]) == 0)
			{
				rUnit = (LengthUnitsEnum)i;
				break;
			}
		}
		if (i == sizeof(_szUnits)/sizeof(_szUnits[0]))
			return (0);
		return (*this);
	}

// Operators
public:
	/**
	 * Converts attribute value to bool
	 * @return true or false
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator bool() const
	{
		if (!m_strAttrValue.CompareNoCase(_T("true")))
			return (true);
		if (!m_strAttrValue.CompareNoCase(_T("false")))
			return (false);
		return (((short)*this ? true : false));
	}

	/**
	 * Converts attribute value to BYTE (unsigned char)
	 * @return the left-most character of attribute value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator BYTE() const
		{ return ((BYTE)(m_strAttrValue.GetLength() ? m_strAttrValue[0] : 0)); }
	
	/**
	 * Converts attribute value to double
	 * @return 0.00 on failure, otherwise, a numeric value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator double() const
		{ return (::_tcstod(m_strAttrValue, NULL)); }
	
	/**
	 * Converts attribute value to signed short int
	 * @return 0 on failure, otherwise, an integer value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator short() const
		{ return ((short)::_ttoi(m_strAttrValue)); }
	
	/**
	 * @return attribute value
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	operator LPCTSTR() const
		{ return (m_strAttrValue); }

// Private Operations
private:
	/**
	 * Sets the value of an attribute. Takes care of the following:
	 *  1. Ignores leading and trailing white-space characters
	 *  2. Replaces character entities with appropriate characters.
	 *  3. Ignores line feeds (LF).
	 *  4. Replaces each carriage-return (CR) or tab with a single space.
	 *
	 * @param lpszValue - new attribute value
	 * 
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	void putValue(LPCTSTR lpszValue)
	{
		ASSERT(AfxIsValidString(lpszValue));

		m_strAttrValue = lpszValue;
		
		// ignore leading white-spaces
		m_strAttrValue.TrimLeft();

		// ignore trailing white-spaces
		m_strAttrValue.TrimRight();

		// ignore line feeds
		m_strAttrValue.Remove(_T('\n'));

		// replace tab and carriage-return with a single space
		m_strAttrValue.Replace(_T('\r'), _T(' '));
		m_strAttrValue.Replace(_T('\t'), _T(' '));

		/** resolve entity reference(s) */
		int		iCurPos = -1, iParseLen = 0;
		TCHAR	chSubst = 0;
		do
		{
			if ((iCurPos = m_strAttrValue.Find(_T('&'), ++iCurPos)) == -1)
				break;
			
			iParseLen = CLiteHTMLEntityResolver::resolveEntity(m_strAttrValue.Mid(iCurPos), chSubst);
			if (iParseLen)
			{
				m_strAttrValue.Replace
				(
					m_strAttrValue.Mid(iCurPos, iParseLen), 
					CString(chSubst)
				);
			}
		}
		while (true);
	}

// Parsing Helpers
public:
	// parses an attribute/value pair from the given string
	UINT parseFromStr(LPCTSTR lpszString);

// Data Members
public:
	static const COLORREF		_clrInvalid;	// an invalid color
	static const unsigned short	_percentMax;	// maximum allowable percentage value
private:
	typedef CMap<CString, LPCWSTR, COLORREF, COLORREF>	CNamedColors;

	static CNamedColors		_namedColors;	// collection of named colors
	CString					m_strAttrName,  // attribute name
							m_strAttrValue; // attribute value
};

/**   
   * String analyzer
   * @param lpszString string ti analyze
   * @return number of TCHARs successfully parsed
*/
inline UINT CLiteHTMLElemAttr::parseFromStr(LPCTSTR lpszString)
{
	ASSERT(AfxIsValidString(lpszString));

	LPCTSTR	lpszBegin = lpszString;
	LPCTSTR	lpszEnd;
	TCHAR	ch = 0;

	// skip leading white-space characters
	while (::_istspace(*lpszBegin))
		lpszBegin = ::_tcsinc(lpszBegin);

	// name doesn't begin with an alphabet?
	if (!::_istalpha(*lpszBegin))
		return (0U);

	lpszEnd = lpszBegin;
	do
	{
		// attribute name may contain letters (a-z, A-Z), digits (0-9), 
		// underscores '_', hyphen '-', colons ':', and periods '.'
		if ( (!::_istalnum(*lpszEnd)) && 
			 (*lpszEnd != _T('-')) && (*lpszEnd != _T(':')) && 
			 (*lpszEnd != _T('_')) && (*lpszEnd != _T('.')) )
		{
			ASSERT(lpszEnd != lpszBegin);

			// only white-space characters, a null-character, an 
			// equal-sign, a greater-than symbol, or a forward-slash 
			// can act as the separator between an attribute and its 
			// value
			if (*lpszEnd == NULL || ::_istspace(*lpszEnd) || 
				*lpszEnd == _T('=') || 
				*lpszEnd == _T('>') || *lpszEnd == _T('/'))
			{
				break;
			}

			return (0U);	// any other character will fail parsing process
		}

		lpszEnd = ::_tcsinc(lpszEnd);
	}
	while (true);

	// extract attribute name
	CString	strAttrName(lpszBegin, lpszEnd - lpszBegin);
	
	if (*lpszEnd != _T('='))
	{
		m_strAttrName = strAttrName;
		m_strAttrValue.Empty();
		return (lpszEnd - lpszString);
	}
	else
	{
		// skip white-space characters after equal-sign 
		// and the equal-sign itself
		do {
			lpszEnd = ::_tcsinc(lpszEnd);
		} while (::_istspace(*lpszEnd));

		lpszBegin = lpszEnd;
		ch = *lpszEnd;
		
		// is attribute value wrapped in quotes?
		if (ch == _T('\'') || ch == _T('\"'))
		{
			lpszBegin = ::_tcsinc(lpszBegin);	// skip quote symbol
			do
			{
				lpszEnd = ::_tcsinc(lpszEnd);
			}
			// Loop until we find the same quote character that 
			// was used at the starting of the attribute value.
			// Anything within these quotes is considered valid!
			// NOTE that the entity references are resolved later.
			while (*lpszEnd != NULL && *lpszEnd != ch);
		}

		// open attribute value i.e. not wrapped in quotes?
		else
		{
			do 
			{ 
				lpszEnd = ::_tcsinc(lpszEnd);
			}
			// loop until we find a tag ending delimeter or any 
			// white-space character, or until we reach at the 
			// end of the string buffer
			while (*lpszEnd != NULL && !::_istspace(*lpszEnd) && 
				   *lpszEnd != _T('/') && *lpszEnd != _T('>'));
		}

		m_strAttrName = strAttrName;
		if (lpszEnd == lpszBegin)	// empty attribute value?
			m_strAttrValue.Empty();
		else
			// use putValue() instead of direct assignment; 
			// this will automatically normalize data before 
			// assigning according to the specs and will 
			// also resolve entity references!!!
			putValue(CString(lpszBegin, lpszEnd - lpszBegin));

		// calculate and return the count of characters successfully parsed
		return ((lpszEnd - lpszString) + 
				(ch == _T('\'') || ch == _T('\"') ? sizeof(TCHAR) : 0) );
	}

	return (0U);
}

/**   
   * CLiteHTMLAttributes Class is defined 
   * Where is the constructor and update
*/
class CLiteHTMLAttributes
{
// Construction/Destruction
public:
	CLiteHTMLAttributes() 
		: m_parrAttrib(NULL)
	{ }

	/**
	 * @param bCopy - if true, this CLiteHTMLAttributes makes a copy 
	 * of the encapsulated pointer. if false, this constructor takes 
	 * ownership of the encapsulated pointer.
	 *
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLAttributes(CLiteHTMLAttributes &rSource, bool bCopy = false) throw(CMemoryException) 
		: m_parrAttrib(NULL)
	{
		if (!bCopy)
		{
			m_parrAttrib = rSource.m_parrAttrib;
			rSource.m_parrAttrib = NULL;
		}
		else
		{
			const int	nElemCount = rSource.getCount();
			if (nElemCount)
			{
				if ((m_parrAttrib = new CElemAttrArray) == NULL)
					AfxThrowMemoryException();
				
				CLiteHTMLElemAttr	*pItem = NULL;
				m_parrAttrib->SetSize(nElemCount);
				
				/** DEEP COPY BEGIN */
				for (int iElem = 0; iElem < nElemCount; iElem++)
				{
					if ((pItem = new CLiteHTMLElemAttr(rSource[iElem])) == NULL)
					{
						removeAll();
						AfxThrowMemoryException();
						return;
					}
					
					(*m_parrAttrib)[iElem] = pItem;
					pItem = NULL;
				}
				/** DEEP COPY END */
			}
		}
	}

	virtual ~CLiteHTMLAttributes()
		{ removeAll(); }

// Initialization
public:
	// parses attribute/value pairs from the given string
	UINT parseFromStr(LPCTSTR lpszString);

// Attributes
public:
	/**
	 * Returns the count of CLiteHTMLElemAttr items in this collection
	 * @return number of items
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	int getCount(void) const
	{
		if (m_parrAttrib != NULL)
			return (m_parrAttrib->GetUpperBound() + 1);
		return (0);
	}

	/**
	 * Look up the index of an attribute given its name.
	 * If more than one attribute with the same name exist, 
	 * this will return the index of the first match.
	 *
	 * @param lpszAttributeName - name of the attribute
	 *
	 * @return zero-based index of an attribute, or -1 if not found
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	int getIndexFromName(LPCTSTR lpszAttributeName) const
	{
		ASSERT(AfxIsValidString(lpszAttributeName));
		CLiteHTMLElemAttr	*pItem = NULL;
		for (int iElem = 0; iElem < getCount(); iElem++)
		{
			if ((pItem = (*m_parrAttrib)[iElem]) == NULL)	// just in case
				continue;
			
			// perform a CASE-INSENSITIVE search
			if (pItem->m_strAttrName.CompareNoCase(lpszAttributeName) == 0)
				return (iElem);
		}
		return (-1);
	}

	/**
	 * Returns a CLiteHTMLElemAttr object given an attribute's index
	 *
	 * @return CLiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLElemAttr operator[](int nIndex) const
	{
		if (!(nIndex >= 0 && nIndex < getCount()))
		{
			ASSERT(FALSE);
			return (CLiteHTMLElemAttr());
		}
		return ( *((*m_parrAttrib)[nIndex]) );
	}

	/**
	 * Returns a CLiteHTMLElemAttr object given an attribute name
	 *
	 * @return CLiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLElemAttr operator[](LPCTSTR lpszIndex) const
	{
		ASSERT(AfxIsValidString(lpszIndex));
		return ((*this)[getIndexFromName(lpszIndex)]);
	}

	/**
	 * Returns a CLiteHTMLElemAttr object given an attribute's index
	 *
	 * @return CLiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLElemAttr getAttribute(int nIndex) const
		{ return ((*this)[nIndex]); }

	/**
	 * Returns a CLiteHTMLElemAttr object given an attribute name
	 *
	 * @return CLiteHTMLElemAttr containing the name and value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLElemAttr getAttribute(LPCTSTR lpszIndex) const
	{
		ASSERT(AfxIsValidString(lpszIndex));
		return ((*this)[getIndexFromName(lpszIndex)]);
	}

	/**
	 * Returns the name of an attribute given its index
	 *
	 * @return name of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getName(int nIndex) const
		{ return ((*this)[nIndex].m_strAttrName); }

	/**
	 * Returns the value of an attribute given its index
	 *
	 * @return value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getValue(int nIndex) const
		{ return ((*this)[nIndex].m_strAttrValue); }

	/**
	 * Returns the value of an attribute given its name
	 *
	 * @return value of an attribute
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CString getValueFromName(LPCTSTR lpszAttributeName) const
		{ return ((*this)[lpszAttributeName].m_strAttrValue); }

// Operations
public:
	/**
	 * Adds a new CLiteHTMLElemAttr item to the collection
	 *
	 * @param lpszName - attribute name (serves as the key to the item)
	 * @param lpszValue - attribute value
	 * @param bReplaceOld - If an item with the same name as specified 
	 *        by lpszName already exists in the collection, this 
	 *        parameter is used to determine whether to replace the 
	 *        existing item or add a new one
	 *
	 * @return pointer to a CLiteHTMLElemAttr
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	CLiteHTMLElemAttr* addAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
	{
		ASSERT(AfxIsValidString(lpszName));
		ASSERT(AfxIsValidString(lpszValue));

		CLiteHTMLElemAttr	*pItem = new CLiteHTMLElemAttr(lpszName, lpszValue);
		if (pItem != NULL)
		{
			if (m_parrAttrib == NULL)
			{
				if ((m_parrAttrib = new CElemAttrArray) == NULL)
				{
					SAFE_DELETE_POINTER(pItem);
					TRACE0("(Error) CLiteHTMLAttributes::addAttribute: Out of memory.\n");
					return (NULL);
				}
			}
			
			VERIFY(m_parrAttrib->Add(pItem) >= 0);
		}
		return (pItem);
	}
	
	/**
	 * Removes an CLiteHTMLElemAttr item from the collection
	 *
	 * @param lpszName - attribute to remove
	 *
	 * @return true if successful, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool removeAttribute(int nIndex)
	{
		if (!(nIndex >= 0 && nIndex < getCount()))
			return (false);
		CLiteHTMLElemAttr	*pItem = NULL;
		VERIFY(((*m_parrAttrib)[nIndex]) != NULL);
		SAFE_DELETE_POINTER(pItem);
		return (true);
	}
	
	/**
	 * Removes all CLiteHTMLElemAttr items from the collection
	 * @return true if successful, false otherwise
	 * @since 1.0
	 * @author Gurmeet S. Kochar
	 */
	bool removeAll(void)
	{
		CLiteHTMLElemAttr	*pItem = NULL;
		for (int iElem = 0; iElem < getCount(); iElem++)
		{
			VERIFY((pItem = (*m_parrAttrib)[iElem]) != NULL);
			SAFE_DELETE_POINTER(pItem);
		}
		SAFE_DELETE_POINTER(m_parrAttrib);
		return (true);
	}

// Data Members
private:
	typedef CTypedPtrArray<CPtrArray, CLiteHTMLElemAttr*>	CElemAttrArray;
	CElemAttrArray	*m_parrAttrib;	// array of attributes/value pairs
};

/**
 * CLiteHTMLAttributes::parseFromStr
 *
 * @param lpszString - string to parse. It can contain pairs such as: 
 *
 *          1. NAME
 *          2. NAME=VALUE
 *          3. NAME='VALUE'
 *          4. NAME="VALUE"
 *
 *        NAME consist of letters, digits, underscores, 
 *        colons, hyphens, and periods
 *
 *        NOTE that white-spaces between NAME and equal-sign AND 
 *        equal-sign and VALUE is allowed.
 *
 * @return number of TCHARs successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
inline UINT CLiteHTMLAttributes::parseFromStr(LPCTSTR lpszString)
{
	ASSERT(AfxIsValidString(lpszString));

	CElemAttrArray		*pcoll = NULL;
	CLiteHTMLElemAttr	oElemAttr;
	const UINT			nStrLen = ::_tcslen(lpszString);
	UINT				nRetVal = 0U, 
						nTemp = 0U;

	do
	{
		// try to parse an attribute/value 
		// pair from the rest of the string
		if (!(nTemp = oElemAttr.parseFromStr(&lpszString[nRetVal])))
		{
			if (!nRetVal)
				goto LError;
			break;
		}

		// collection has not been instantiated until now?
		if (pcoll == NULL)
		{
			// instantiate now
			if ((pcoll = new CElemAttrArray) == NULL)
				// out of memory?
			{
				TRACE0("(Error) CLiteHTMLAttributes::parseFromStr: Out of memory.\n");
				goto LError;
			}
		}

		// add attribute/value pair to collection
		if (pcoll->Add(new CLiteHTMLElemAttr(oElemAttr)) < 0)
			goto LError;

		// advance seek pointer
		nRetVal += nTemp;
	}
	
	// do we still have something in the buffer to parse?
	while (nRetVal < nStrLen);

	// collection was never instantiated?
	if (pcoll == NULL)
		goto LError;
	// collection is empty?
	if (pcoll->GetUpperBound() == -1)
		goto LError;
	// current collection could not be emptied?
	if (!removeAll())
		goto LError;

	m_parrAttrib = pcoll;
	pcoll = NULL;
	goto LCleanExit;	// success!

LError:
	SAFE_DELETE_POINTER(pcoll);
	nRetVal = 0U;

LCleanExit:
	return (nRetVal);
}

#pragma warning(default : 4290)
#pragma warning(pop)

#endif	// !__LITEHTMLATTRIBUTES_H__
